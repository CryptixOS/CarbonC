/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <Carbon/Core/Compiler.hpp>
#include <assert.h>

namespace Carbon
{
    extern "C"
    {
        CC_NORETURN extern void __assert_fail(const char*  expr,
                                              const char*  file,
                                              unsigned int line,
                                              const char*  function)
        {
            AssertFmt("Assertion Failed({}::{}:{}): {}", file, function, line,
                      expr);
            AssertNotReached();
        }
    }
}; // namespace Carbon
