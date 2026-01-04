/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#ifndef _POSIX_CTYPE_H
#define _POSIX_CTYPE_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#include <bits/types/locale_t.h>

int isalnum_l(int __c, locale_t __loc);
int isalpha_l(int __c, locale_t __loc);
int isblank_l(int __c, locale_t __loc);
int iscntrl_l(int __c, locale_t __loc);
int isdigit_l(int __c, locale_t __loc);
int isgraph_l(int __c, locale_t __loc);
int islower_l(int __c, locale_t __loc);
int isprint_l(int __c, locale_t __loc);
int ispunct_l(int __c, locale_t __loc);
int isspace_l(int __c, locale_t __loc);
int isupper_l(int __c, locale_t __loc);
int isxdigit_l(int __c, locale_t __loc);

int isascii_l(int __c, locale_t __loc);

int tolower_l(int __c, locale_t __loc);
int toupper_l(int __c, locale_t __loc);

__END_DECLS
#endif /* _POSIX_CTYPE_H */
