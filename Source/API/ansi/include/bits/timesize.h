/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <bits/wordsize.h>

#if defined __x86_64__ && defined __ILP32__
    #define __TIMESIZE 64
#else
    #define __TIMESIZE __WORDSIZE
#endif
