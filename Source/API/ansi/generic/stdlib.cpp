/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <Carbon/Core/CarbonC.hpp>
#include <Carbon/Platform/posix/Sysdeps.hpp>
#include <stdlib.h>

namespace Carbon
{
    extern "C"
    {
        int  __cxa_atexit(void (*function)(void*), void* argument,
                          void* dso_tag);
        void abort(void) throw() { PrismToDo(); }

        int  atexit(void (*func)(void))
        {
            __cxa_atexit((void (*)(void*))func, nullptr, nullptr);
            return 0;
        }
        int at_quick_exit(void (*func)(void))
        {
            IgnoreUnused(func);
            Assert(!"Not implemented");
            AssertNotReached();
        }

        void exit(int status)
        {
            Assert(ShutdownLibrary());
            Carbon::Sysdeps::Exit(status);
        }

        void _Exit(int status) { Carbon::Sysdeps::Exit(status); }

        void quick_exit(int)
        {
            Assert(!"Not implemented");
            AssertNotReached();
        }

        extern char** environ;
    };
}; // namespace Carbon
