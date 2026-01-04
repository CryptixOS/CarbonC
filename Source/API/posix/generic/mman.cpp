/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Types.hpp>
#include <Carbon/Platform/posix/Sysdeps.hpp>
#include <errno.h>
#include <sys/mman.h>

extern "C"
{
    using namespace Carbon;
    void* mmap(void* address, usize size, i32 prot, i32 flags, i32 fd,
               off_t offset)
    {
        void* window = nullptr;
        if (int e = Sysdeps::MemoryMap(address, size, prot, flags, fd, offset,
                                       &window);
            e)
        {
            errno = e;
            return MAP_FAILED;
        }

        return window;
    }
    i32 munmap(void* addr, usize size)
    {
        return Sysdeps::MemoryUnmap(addr, size);
    }
};
