/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Prism/Debug/Log.hpp>

#define CarbonDebug(...) PrismDebug(__VA_ARGS__)
#define CarbonTrace(...) PrismTrace(__VA_ARGS__)
#define CarbonInfo(...) PrismInfo(__VA_ARGS__)
#define CarbonError(...) PrismError(__VA_ARGS__)
#define CarbonFatal(...) PrismFatal(__VA_ARGS__)
