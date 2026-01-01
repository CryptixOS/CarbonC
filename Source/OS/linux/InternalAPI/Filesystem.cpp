/*
 * Created by v1tr10l7 on 17.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Platform/posix/unistd.h>
#include <linux/syscall.h>

namespace Carbon::InternalAPI
{
    isize Write(i32 fd, const void* buffer, usize count)
    {
        auto nwritten = Syscall(SYS_WRITE, fd, buffer, count);
        if (!nwritten) return -1;

        return nwritten;
    }
} // namespace Carbon::InternalAPI
