/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#ifndef _BITS_TYPES_H
    #error "Never include <bits/time64.h> directly; use <sys/types.h> instead."
#endif

#ifndef _BITS_TIME64_H
    #define _BITS_TIME64_H 1

/* Define __TIME64_T_TYPE so that it is always a 64-bit type.  */

    #if __TIMESIZE == 64
        /* If we already have 64-bit time type then use it.  */
        #define __TIME64_T_TYPE __TIME_T_TYPE
    #else
        /* Define a 64-bit time type alongsize the 32-bit one.  */
        #define __TIME64_T_TYPE __SQUAD_TYPE
    #endif

#endif /* bits/time64.h */
