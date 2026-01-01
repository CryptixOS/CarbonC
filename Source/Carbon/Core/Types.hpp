/*
 * Created by v1tr10l7 on 13.07.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Prism/Core/Compiler.hpp>

namespace Carbon
{
    using namespace Prism;

    using i8       = __INT8_TYPE__;
    using i16      = __INT16_TYPE__;
    using i32      = __INT32_TYPE__;
    using i64      = __INT64_TYPE__;

    using u8       = __UINT8_TYPE__;
    using u16      = __UINT16_TYPE__;
    using u32      = __UINT32_TYPE__;
    using u64      = __UINT64_TYPE__;

    using isize    = __PTRDIFF_TYPE__;
    using usize    = __SIZE_TYPE__;

    using ipointer = __INTPTR_TYPE__;
    using upointer = __UINTPTR_TYPE__;
}; // namespace Carbon
