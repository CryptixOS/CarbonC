/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS
[[noreturn]]
extern void __assert_fail(const char* expr, const char* file, unsigned int line,
                          const char* function);

[[noreturn]]
void __assert(const char* expr, const char* filename, int line);
#ifndef NDEBUG
    #define assert(expr)                                                       \
        (__builtin_expect(!(expr), 0)                                          \
             ? __assert_fail(#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__)   \
             : (void)0)

#else
    #define assert(expr) ((void)(0))
#endif

__END_DECLS
