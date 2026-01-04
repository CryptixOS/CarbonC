/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#ifndef _CTYPE_H
    #define _CTYPE_H 1

    #include <features.h>
    #include <sys/cdefs.h>

__BEGIN_DECLS

    #include <bits/endian.h>
    #if __BYTE_ORDER == __BIG_ENDIAN
        #define _ISbit(bit) (1 << (bit))
    #else /* __BYTE_ORDER == __LITTLE_ENDIAN */
        #define _ISbit(bit)                                                    \
            ((bit) < 8 ? ((1 << (bit)) << 8) : ((1 << (bit)) >> 8))
    #endif
/* Character classification function [7.4.1] */
int isalnum(int __c);
int isalpha(int __c);
int isblank(int __c);
int iscntrl(int __c);
int isdigit(int __c);
int isgraph(int __c);
int islower(int __c);
int isprint(int __c);
int ispunct(int __c);
int isspace(int __c);
int isupper(int __c);
int isxdigit(int __c);

/* glibc extensions. */
int isascii(int __c);

/* Character case mapping functions [7.4.2] */
int tolower(int __c);
int toupper(int __c);

    /* Borrowed from glibc */
    #define toascii(c) ((c) & 0x7f)

__END_DECLS

    #include <bits/posix_ctype.h>
#endif /* ctype.h  */
