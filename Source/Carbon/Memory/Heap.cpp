/*
 * Created by v1tr10l7 on 01.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Memory/Heap.hpp>
#include <sys/mman.h>

namespace Carbon
{
    namespace Heap
    {
        // FIXME(v1tr10l7): get actual, non-hardcoded page size
        inline static constexpr usize PAGE_SIZE = 0x1000;
        inline static Pointer         allocatePages(usize pageCount = 1)
        {
            Pointer address
                = mmap(nullptr, pageCount * PAGE_SIZE, PROT_READ | PROT_WRITE,
                       MAP_ANONYMOUS, -1, 0);

            return address;
        }
        inline static void freePages(Pointer address, usize pageCount = 1)
        {
            munmap(address, pageCount * PAGE_SIZE);
        }

        struct PageAllocPolicy
        {
            static Pointer CallocatePages(usize pageCount = 1)
            {
                return Pointer(allocatePages(pageCount));
            }
            static void FreePages(Pointer memory, usize pageCount = 1)
            {
                freePages(memory, pageCount);
            }
        };

        class SpinLockPolicy
        {
          public:
            void                    Init() {}
            PM_NODISCARD ScopedLock Lock() { return ScopedLock(m_Lock); }

          private:
            Spinlock m_Lock;
        };

        namespace
        {
            constexpr usize BUCKET_COUNT         = 8;

            bool            s_Initialized        = false;
            Pointer         s_EarlyHeapBase      = nullptr;
            usize           s_EarlyHeapSize      = 0;
            usize           s_EarlyHeapAllocated = 0;
            Pointer         s_EarlyHeapCurrent   = nullptr;

            alignas(SlabPool<8, PageAllocPolicy, SpinLockPolicy>) static u8
                s_SlabPoolStorage[sizeof(
                    SlabPool<8, PageAllocPolicy, SpinLockPolicy>)];
            static SlabPool<8, PageAllocPolicy, SpinLockPolicy>* s_SlabPool
                = nullptr;

            Pointer EarlyHeapAllocate(usize size)
            {
                size = Math::AlignUp(size, sizeof(void*));
                Assert(s_EarlyHeapSize - s_EarlyHeapAllocated > size);

                auto memory = s_EarlyHeapCurrent;
                s_EarlyHeapCurrent += size;
                s_EarlyHeapAllocated += size;

                return memory;
            }
        } // namespace
        void    Initialize();

        Pointer Allocate(usize bytes);
        Pointer Callocate(usize bytes);
        Pointer Reallocate(Pointer address, usize size);

        void    Free(Pointer memory);
    }; // namespace Heap
}; // namespace Carbon
