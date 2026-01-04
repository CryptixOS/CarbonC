/*
 * Created by v1tr10l7 on 01.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Carbon/Core/Types.hpp>
#include <Prism/Memory/Memory.hpp>

namespace Carbon
{
    namespace Heap
    {
        inline static constexpr usize DEFAULT_SIZE = 16_kib;

        void                          Initialize();

        // TODO(v1tr10l7): alignment
        Pointer                       Allocate(usize bytes);
        Pointer                       Callocate(usize bytes);
        Pointer                       Reallocate(Pointer address, usize size);

        void                          Free(Pointer memory);
    }; // namespace Heap
}; // namespace Carbon
