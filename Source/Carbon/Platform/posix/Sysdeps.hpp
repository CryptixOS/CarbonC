/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Carbon/Core/Compiler.hpp>
#include <Carbon/Core/Types.hpp>

namespace Carbon
{
    namespace Sysdeps
    {
        isize Write(i32 fd, const void* buffer, usize count);
        int MemoryMap(void* address, usize length, i32 prot, i32 flags, i32 fd,
                      i64 offset, void** window);
        i32 MemoryUnmap(void* address, usize bytes);
        CC_NORETURN void Exit(int status);
    }; // namespace Sysdeps
}; // namespace Carbon
