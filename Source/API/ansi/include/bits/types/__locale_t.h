/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#ifndef _BITS_TYPES___LOCALE_T_H
    #define _BITS_TYPES___LOCALE_T_H 1

struct __locale_struct
{
    /* Note: LC_ALL is not a valid index into this array.  */
    struct __locale_data*     __locales[13]; /* 13 = __LC_LAST. */

    /* To increase the speed of this solution we add some special members.  */
    const unsigned short int* __ctype_b;
    const int*                __ctype_tolower;
    const int*                __ctype_toupper;

    /* Note: LC_ALL is not a valid index into this array.  */
    const char*               __names[13];
};

typedef struct __locale_struct* __locale_t;
#endif /* bits/types/__locale_t.h */
