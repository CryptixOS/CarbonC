/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Log.hpp>
#include <Carbon/Core/Panic.hpp>
#include <Carbon/Platform/posix/Sysdeps.hpp>

namespace Carbon
{
    CC_NORETURN void Panic(StringView message)
    {
        using namespace Sysdeps;
        CarbonError(
            "CarbonC: Library crashed!\n"
            "Error Message:\n{}",
            message);

        Exit(EXIT_FAILURE);
    }
}; // namespace Carbon
