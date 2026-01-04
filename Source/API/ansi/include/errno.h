/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <bits/errno.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

#if CARBONC_TLS
extern __thread int __carbonc_errno;
#endif

typedef int errno_t;
errno_t*    __errno_location(void) __attribute__((const));
#define errno    (*__errno_location())

#define no_error ((errno_t)0)
#define return_err(ret, err)                                                   \
    do                                                                         \
    {                                                                          \
        errno = err;                                                           \
        return ret;                                                            \
    } while (0)

/* Linux extensions. */
extern char* program_invocation_name;
extern char* program_invocation_short_name;
extern char* __progname;
extern char* __progname_full;

__END_DECLS
