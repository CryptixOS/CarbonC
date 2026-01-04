/*
 * Created by v1tr10l7 on 17.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <linux/syscall.h>

namespace Carbon::Sysdeps
{
    void Exit(int status)
    {
        Syscall(SYS_EXIT, status);
        AssertNotReached();
    }
}; // namespace Carbon::Sysdeps
