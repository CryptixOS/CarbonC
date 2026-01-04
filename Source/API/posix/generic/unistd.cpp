/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Platform/posix/Sysdeps.hpp>

namespace Carbon
{
    extern "C"
    {
        isize write(i32 fd, const void* buffer, usize count)
        {
            return Sysdeps::Write(fd, buffer, count);
        }
    };
}; // namespace Carbon
