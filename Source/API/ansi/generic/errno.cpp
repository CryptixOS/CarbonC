/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <errno.h>

namespace Carbon
{
    extern "C"
    {
        errno_t __thread __carbonc_errno;

        char*        program_invocation_name       = nullptr;
        char*        program_invocation_short_name = nullptr;
        extern char* __progname __attribute__((
            __weak__, __alias__("program_invocation_short_name")));
        extern char* __progname_full
            __attribute__((__weak__, __alias__("program_invocation_name")));

        int* __errno_location(void) { return &__carbonc_errno; }
    };
}; // namespace Carbon
