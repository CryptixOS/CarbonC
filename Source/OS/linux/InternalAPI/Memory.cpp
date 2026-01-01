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
    void* MemoryMap(void* address, usize length, i32 prot, i32 fd, i64 offset)
    {
        auto memory = Syscall(SYS_MMAP, address, length, prot, fd, offset);
        if (!memory) return reinterpret_cast<void*>(-1);

        return reinterpret_cast<void*>(static_cast<i64>(memory));
    }
} // namespace Carbon::InternalAPI
