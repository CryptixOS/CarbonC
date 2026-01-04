/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <Carbon/Core/Log.hpp>
#include <Carbon/Core/Panic.hpp>
#include <Carbon/Memory/Heap.hpp>
#include <Carbon/Platform/posix/Sysdeps.hpp>
#include <Prism/Core/Error.hpp>
#include <Prism/Core/Eternal.hpp>

#if CARBONC_ARCH == CARBONC_ARCH_X86_64
    #include <immintrin.h>
#endif
#include <cxxabi.h>

namespace Carbon
{
    using namespace Prism;
    using ConstructorFunction = void (*)();
    using DestructorFunction  = void (*)(void*);

    struct AtExitFunctionEntry
    {
        DestructorFunction Function  = nullptr;
        void*              Object    = nullptr;
        void*              DsoHandle = nullptr;
    };
    using DestructorQueue = Vector<AtExitFunctionEntry>;

    inline static constexpr usize ATEXIT_MAX_ENTRY_COUNT = 128;

    DestructorQueue&              ExitQueue()
    {
        static DestructorQueue queue;

        return queue;
    }

    extern "C"
    {
        using namespace Carbon;
        extern ConstructorFunction __init_array_start[];
        extern ConstructorFunction __init_array_end[];

        extern DestructorFunction  __fini_array_start[];
        extern DestructorFunction  __fini_array_end[];

        CC_HIDDEN
        void* __dso_handle;
        i32   __cxa_atexit(DestructorFunction func, void* objptr, void* dso)
        {
            AtExitFunctionEntry handler;
            handler.Function  = func;
            handler.Object    = objptr;
            handler.DsoHandle = dso;

            ExitQueue().EmplaceBack(func, objptr, dso);
            return EXIT_SUCCESS;
        }
        void __cxa_finalize(void* dso)
        {
            auto eq = ExitQueue();

            for (usize i = eq.Size(); i > 0; i--)
            {
                auto& handler = eq[i - 1];
                if (!handler.Function) continue;

                if (!dso || handler.DsoHandle == dso)
                {
                    handler.Function(handler.Object);
                    handler.Function = nullptr;
                }
            }
        }

        void __cxa_pure_virtual()
        {
            Panic("__cxa_pure_virtual()");
            AssertNotReached();
        }

        upointer __stack_chk_guard = 0;

        CC_NORETURN
        void __stack_chk_fail()
        {
            Panic("carbonc: stack smashing detected!");
            __builtin_unreachable();
        }

        CC_UNUSED
        void CC_NO_STACK_PROTECTOR __guard_setup(void)
        {
            u8* p;
            if (__stack_chk_guard != 0) return;
#if CTOS_ARCH == CTOS_ARCH_X86_64
            if (_rdrand64_step(
                    reinterpret_cast<unsigned long long*>(&__stack_chk_guard))
                && __stack_chk_guard != 0)
                return;
#endif
            /* If a random generator can't be used, the protector switches the
               guard to the "terminator canary".  */
            p = reinterpret_cast<u8*>(&__stack_chk_guard);
            p[sizeof(__stack_chk_guard) - 1] = 255;
            p[sizeof(__stack_chk_guard) - 2] = '\n';
            p[0]                             = 0;
        }
    }
    ErrorOr<void> InitializeLibrary()
    {
        Heap::Initialize();

        CarbonDebug("CarbonC: Invoking global constructors...");
        for (auto entry = __init_array_start; entry < __init_array_end; entry++)
        {
            auto constructor = *entry;
            constructor();
        }

        CarbonDebug("CarbonC: All global constructors called");
        return {};
    }

    CC_DESTRUCTOR void FinalizeDso() { __cxa_finalize(&__dso_handle); }

    void               InvokeDestructors()
    {
        isize fini_count = __fini_array_end - __fini_array_start;
        for (isize i = fini_count - 1; i >= 0; i--)
        {
            auto destructor
                = reinterpret_cast<void (*)()>(__fini_array_start[i]);
            if (destructor) destructor();
        }
    }
    void InvokeAtExitHandlers()
    {
        auto eq = ExitQueue();
        for (usize i = eq.Size(); i > 0; i--)
        {
            auto& handler = eq[i - 1];
            if (!handler.Function) continue;

            if (!handler.DsoHandle)
            {
                handler.Function(handler.Object);
                handler.Function = nullptr;
            }
        }

        InvokeDestructors();
    }

    ErrorOr<void> ShutdownLibrary()
    {
        CarbonDebug("CarbonC: Shutting down the library...");

        // Call atexit and __cxa_atexit handlers
        // Passing 0 (NULL) to __cxa_finalize tells it to call EVERYTHING
        // in the registration stack in reverse order.
        CarbonDebug("CarbonC: Finalizing atexit handlers...");
        __cxa_finalize(&__dso_handle);

        CarbonDebug("CarbonC: Invoking global destructors (.fini_array)...");
        InvokeDestructors();

        CarbonDebug("CarbonC: Shutdown complete.");
        return {};
    }
}; // namespace Carbon

namespace std
{
    void terminate() CC_NOEXCEPT
    {
        Carbon::ShutdownLibrary();
        Carbon::Sysdeps::Exit(EXIT_FAILURE);
    }
}; // namespace std

namespace __cxxabiv1
{
    int __cxa_guard_acquire(__guard* guard)
    {
        if ((*guard) & 0x0001) return 0;
        if ((*guard) & 0x0100) __cxa_guard_abort(guard);

        *guard |= 0x0100;
        return 1;
    }

    void __cxa_guard_release(__guard* guard) { *guard |= 0x0001; }

    void __cxa_guard_abort(__guard* guard)
    {
        using namespace Carbon;
        PanicFmt("__cxa_guard_abort({})", static_cast<void*>(guard));
        AssertNotReached();
    }
} // namespace __cxxabiv1
