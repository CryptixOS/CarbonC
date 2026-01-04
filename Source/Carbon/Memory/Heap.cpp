/*
 * Created by v1tr10l7 on 01.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <Carbon/Core/Compiler.hpp>
#include <Carbon/Memory/Heap.hpp>
#include <Prism/Memory/SlabPool.hpp>
#include <Prism/Utility/LockingPolicy.hpp>
#include <sys/mman.h>

namespace Carbon
{
    using namespace Prism;
    namespace Heap
    {
        // FIXME(v1tr10l7): get actual, non-hardcoded page size
        inline static constexpr usize PAGE_SIZE = 0x1000;
        inline static Pointer         allocatePages(usize pageCount = 1)
        {
            upointer address = Pointer(mmap(nullptr, pageCount * PAGE_SIZE,
                                            PROT_READ | PROT_WRITE,
                                            MAP_ANONYMOUS | MAP_PRIVATE, -1, 0))
                                   .Raw();
            Assert(reinterpret_cast<void*>(address) != MAP_FAILED);

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
                auto address = Pointer(allocatePages(pageCount));
                Memory::Fill(address, 0, pageCount * PAGE_SIZE);

                return address;
            }
            static void FreePages(Pointer memory, usize pageCount = 1)
            {
                freePages(memory, pageCount);
            }
        };

        class SpinLockPolicy
        {
          public:
            void         Init() {}
            PM_NODISCARD ScopedLock<NoLock> Lock()
            {
                return ScopedLock<NoLock>(m_Lock);
            }

          private:
            NoLock m_Lock;
        };

        namespace
        {
            CC_UNUSED constexpr usize BUCKET_COUNT  = 8;
            CC_UNUSED bool            s_Initialized = false;

            CC_UNUSED alignas(
                SlabPool<8, PageAllocPolicy, SpinLockPolicy>) static u8
                s_SlabPoolStorage[sizeof(
                    SlabPool<8, PageAllocPolicy, SpinLockPolicy>)];
            CC_UNUSED static SlabPool<8, PageAllocPolicy, SpinLockPolicy>*
                s_SlabPool
                = nullptr;
        } // namespace

        void Initialize()
        {
            PrismTraceNoAlloc("KernelHeap: Initializing...");
            s_SlabPool = new (&s_SlabPoolStorage)
                SlabPool<8, PageAllocPolicy, SpinLockPolicy>();
            s_SlabPool->Initialize();

            s_Initialized = true;
            PrismInfo("KernelHeap: Initialized `{}` slab buckets",
                      BUCKET_COUNT);
        }

        Pointer Allocate(usize bytes)
        {
            if (!s_Initialized) return nullptr;
            return s_SlabPool->Allocate(bytes);
        }
        Pointer Callocate(usize bytes)
        {
            return s_Initialized ? s_SlabPool->Callocate(bytes) : nullptr;
        }
        Pointer Reallocate(Pointer memory, usize size)
        {
            return s_SlabPool->Reallocate(memory, size);
        }
        void Free(Pointer memory) { return s_SlabPool->Free(memory); }
    }; // namespace Heap
}; // namespace Carbon

using namespace Carbon;
void* operator new(usize size) { return Heap::Callocate(size); }
void* operator new(usize size, AlignmentType) { return Heap::Callocate(size); }
void* operator new[](usize size) { return Heap::Callocate(size); }
void* operator new[](usize size, AlignmentType)
{
    return Heap::Callocate(size);
}
void operator delete(void* memory) noexcept { Heap::Free(memory); }
void operator delete(void* memory, AlignmentType) noexcept
{
    Heap::Free(memory);
}
void operator delete(void* memory, usize) noexcept { Heap::Free(memory); }
void operator delete[](void* memory) noexcept { Heap::Free(memory); }
void operator delete[](void* memory, AlignmentType) noexcept
{
    Heap::Free(memory);
}
void operator delete[](void* memory, usize) noexcept { Heap::Free(memory); }
