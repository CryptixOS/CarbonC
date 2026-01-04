/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#define CC_NORETURN           [[noreturn]]
#define CC_NOT_USED           [[maybe_unused]]
#define CC_NO_STACK_PROTECTOR __attribute__((no_stack_protector))
