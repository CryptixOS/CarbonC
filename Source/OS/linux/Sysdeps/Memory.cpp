/*
 * Created by v1tr10l7 on 17.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <linux/syscall.h>

namespace Carbon::Sysdeps
{
    int MemoryMap(void* address, usize length, i32 prot, i32 flags, i32 fd,
                  i64 offset, void** window)
    {
        auto ret = Syscall(SYS_MMAP, address, length, prot, flags, fd, offset);
        if (ret.DidFail()) return ret.StatusCode;

        *window = reinterpret_cast<void*>(ret.StatusCode);
        return 0;
    }
    i32 MemoryUnmap(void* address, usize bytes)
    {
        auto ret = Syscall(SYS_UNMAP, address, bytes);
        if (!ret) return -1;

        return ret;
    }
} // namespace Carbon::Sysdeps
