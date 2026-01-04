/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <Carbon/Core/Log.hpp>
#include <Carbon/Core/Panic.hpp>
#include <Prism/Core/Error.hpp>

#if CARBONC_ARCH == CARBONC_ARCH_X86_64
    #include <immintrin.h>
#endif
#include <cxxabi.h>

using namespace Prism;
using ConstructorFunction = void (*)();
using DestructorFunction  = void (*)(void*);

struct AtExitFunctionEntry
{
    DestructorFunction Function;
    void*              Object;
};
inline static constexpr usize ATEXIT_MAX_ENTRY_COUNT = 128;
extern "C"
{
    using namespace Carbon;
    extern ConstructorFunction __init_array_start[];
    extern ConstructorFunction __init_array_end[];

    extern DestructorFunction  __fini_array_start[];
    extern DestructorFunction  __fini_array_end[];

    extern AtExitFunctionEntry __atexit_funcs[ATEXIT_MAX_ENTRY_COUNT];
    usize                      __atexit_func_count = 0;

    void*                      __dso_handle        = 0;
    i32 __cxa_atexit(DestructorFunction func, void* objptr, void* dso)
    {
        if (__atexit_func_count >= ATEXIT_MAX_ENTRY_COUNT) return EXIT_FAILURE;
        __atexit_funcs[__atexit_func_count].Function = func;
        __atexit_funcs[__atexit_func_count].Object   = objptr;
        ++__atexit_func_count;

        return EXIT_SUCCESS;
    }
    void __cxa_finalize(void* f)
    {
        usize i = __atexit_func_count;
        if (!f)
        {
            while (i--)
            {
                if (__atexit_funcs[i].Function)
                    (*__atexit_funcs[i].Function)(__atexit_funcs[i].Object);
            };
            return;
        };

        isize findex = -1;
        for (usize j = 0; j < __atexit_func_count; j++)
        {
            if (__atexit_funcs[j].Function == f)
            {
                (*__atexit_funcs[j].Function)(__atexit_funcs[j].Object);
                __atexit_funcs[j].Function = 0;
                findex                     = j;
            }
        }
        if (findex < 0) return;
        for (u64 j = findex; j < __atexit_func_count; j++)
        {
            __atexit_funcs[j].Function = __atexit_funcs[j + 1].Function;
            __atexit_funcs[j].Object   = __atexit_funcs[j + 1].Object;
        }
        --__atexit_func_count;
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

    CC_NOT_USED
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
            PanicFmt("__cxa_guard_abort({})", static_cast<void*>(guard));
            AssertNotReached();
        }
    } // namespace __cxxabiv1
}

namespace Carbon
{
    ErrorOr<void> Initialize()
    {
        CarbonDebug("CarbonC: Invoking global constructors...");
        for (auto entry = __init_array_start; entry < __init_array_end; entry++)
        {
            auto constructor = *entry;
            constructor();
        }

        CarbonDebug("CarbonC: All global constructors called");
        return {};
    }
    ErrorOr<void> Shutdown()
    {
        CarbonDebug("CarbonC: Shutting down the library...");

        // 1. Call atexit and __cxa_atexit handlers
        // Passing 0 (NULL) to __cxa_finalize tells it to call EVERYTHING
        // in the registration stack in reverse order.
        CarbonDebug("CarbonC: Finalizing atexit handlers...");
        __cxa_finalize(nullptr);

        CarbonDebug("CarbonC: Invoking global destructors (.fini_array)...");
        isize fini_count = __fini_array_end - __fini_array_start;
        for (isize i = fini_count - 1; i >= 0; i--)
        {
            auto destructor
                = reinterpret_cast<void (*)()>(__fini_array_start[i]);
            if (destructor) destructor();
        }

        CarbonDebug("CarbonC: Shutdown complete.");
        return {};
    }
}; // namespace Carbon
