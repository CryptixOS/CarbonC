/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once
#define _POSIX_VERSION 200809L

#ifdef __cplusplus
    #ifndef __BEGIN_DECLS
        #define __BEGIN_DECLS                                                  \
            extern "C"                                                         \
            {
        #define __END_DECLS                                                    \
            }                                                                  \
            ;
    #endif
#elifndef __BEGIN_DECLS
    #define __BEGIN_DECLS
    #define __END_DECLS
#endif

#undef __P
#define __P(a) a
