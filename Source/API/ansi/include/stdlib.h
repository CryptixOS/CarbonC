/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/* [7.22] General utilities */
typedef struct
{
    int quot, rem;
} div_t;

typedef struct
{
    long quot, rem;
} ldiv_t;

typedef struct
{
    long long quot, rem;
} lldiv_t;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX     0x7fffffff
#define MB_CUR_MAX   ((size_t)4)

/* [7.22.1] Numeric conversion functions */
double        atof(const char* __string);
int           atoi(const char* __string);
long          atol(const char* __string);
long long     atoll(const char* __string);
double        strtod(const char* __restrict __string, char** __restrict __end);
float         strtof(const char* __restrict __string, char** __restrict __end);
long double   strtold(const char* __restrict __string, char** __restrict __end);
long          strtol(const char* __restrict __string, char** __restrict __end,
                     int __base);
long long     strtoll(const char* __restrict __string, char** __restrict __end,
                      int __base);
unsigned long strtoul(const char* __restrict __string, char** __restrict __end,
                      int __base);
unsigned long long strtoull(const char* __restrict __string,
                            char** __restrict __end, int __base);

/* [7.22.3] Memory management functions */
void*              aligned_alloc(size_t __alignment, size_t __size);
void*              calloc(size_t __count, size_t __size);
void               free(void* __pointer);
void*              malloc(size_t __size);
void*              realloc(void* __pointer, size_t __size);

int posix_memalign(void** __out, size_t __alignment, size_t __size);

/* [7.22.4] Communication with the environment */
__attribute__((__noreturn__)) void abort(void) throw();
int                                atexit(void (*__func)(void));
int                                at_quick_exit(void (*__func)(void));
__attribute__((__noreturn__)) void exit(int __status);
__attribute__((__noreturn__)) void _Exit(int __status);
char*                              getenv(const char* __name);
__attribute__((__noreturn__)) void quick_exit(int __status);
int                                system(const char* __string);

__END_DECLS
#endif /* _STDLIB_H */
