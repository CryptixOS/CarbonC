/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
void*  memcpy(void* dest, const void* src, size_t len) throw();
int    memcmp(const void* ptr1, const void* ptr2, size_t len) throw();
void*  memset(void* dest, int ch, size_t len) throw();
void*  memmove(void* dest, const void* src, size_t len) throw();
void*  memchr(const void* ptr, int ch, size_t len);

size_t strlen(const char* str) throw();
int    strcmp(const char* str1, const char* str2) throw();
int    strncmp(const char* str1, const char* str2, size_t len) throw();
__END_DECLS
