/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Carbon/Core/Compiler.hpp>
#include <Carbon/Core/Types.hpp>
#include <Prism/String/StringView.hpp>

namespace Carbon
{
    CC_NORETURN void Panic(StringView message);
};

#define PanicFmt(...) Panic(fmt::format(__VA_ARGS__).data())
