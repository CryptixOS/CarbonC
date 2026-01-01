/*
 * Created by v1tr10l7 on 13.07.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Carbon/Core/Types.hpp>

namespace Carbon::InternalAPI
{
    isize Write(i32 fd, const void* buffer, usize count);
    void  Exit(int status);
} // namespace Carbon::InternalAPI
