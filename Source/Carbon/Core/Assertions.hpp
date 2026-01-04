/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Prism/Debug/Assertions.hpp>

#define Assert(...)           PrismAssert(__VA_ARGS__)
#define AssertNotReached(...) PrismNotReached(__VA_ARGS__)
#define AssertFmt(...)        PrismAssertFmt(__VA_ARGS__)
