/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <Carbon/Platform/posix/Sysdeps.hpp>

namespace Carbon
{
    namespace Sysdeps
    {
        CC_WEAK isize Write(i32 fd, const void* buffer, usize count)
        {
            return -1;
        }
        CC_WEAK int MemoryMap(void* address, usize length, i32 prot, i32 flags,
                              i32 fd, off_t offset, void** window)
        {
            return -1;
        }
        CC_WEAK i32  MemoryUnmap(void* address, usize bytes) { return -1; }
        CC_WEAK void Exit(int status) { AssertNotReached(); }
    }; // namespace Sysdeps
}; // namespace Carbon
