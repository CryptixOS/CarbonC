/*
 * Created by v1tr10l7 on 22.05.2024.
 * Copyright (c) 2024-2024, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Types.hpp>
#include <assert.h>
// #include <Prism/Debug/Assertions.hpp>

extern "C"
{
    using namespace Carbon;
    __attribute__((noreturn)) extern void __assert_fail(const char*  expr,
                                                        const char*  file,
                                                        unsigned int line,
                                                        const char*  function)
    {
        // FIXME(v1tr10l7): Panic

        __builtin_unreachable();
        // Stacktrace::Print(6);
        // Panic("Assertion Failed({}::{}:{}): {}", file, function, line, expr);
    }

    __attribute__((noreturn)) void __assert(const char* expr,
                                            const char* filename, i32 line)
    {
        __assert_fail(expr, filename, line, "");
    }
}
