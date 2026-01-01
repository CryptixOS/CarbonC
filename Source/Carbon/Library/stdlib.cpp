/*
 * Created by v1tr10l7 on 16.11.2024.
 * Copyright (c) 2024-2024, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <stdlib.h>

#include <Carbon/Memory/Heap.hpp>

extern "C"
{
    using namespace Carbon;

    void  free(void* ptr) throw() { Heap::Free(ptr); }
    void* malloc(size_t size) throw() { return Heap::Allocate(size); }
    void* realloc(void* oldptr, size_t size) throw()
    {
        return Heap::Reallocate(oldptr, size);
    }

    void abort() throw()
    {
        // FIXME(v1tr10l7): actual assert
        IgnoreUnused("Abort");
        __builtin_unreachable();
    }
} // extern "C"
