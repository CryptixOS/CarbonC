/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Prism/Core/Error.hpp>

namespace Carbon
{
    using namespace Prism;
    ErrorOr<void> InitializeLibrary();
    ErrorOr<void> ShutdownLibrary();
}; // namespace Carbon
