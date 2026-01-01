/*
 * Created by v1tr10l7 on 13.07.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#pragma once

#include <Carbon/Core/Types.hpp>

#define SyscallInvoker "syscall"

namespace Carbon::InternalAPI
{
    struct Status
    {
        constexpr Status() = default;

        template <typename T>
        constexpr Status(T status)
            : StatusCode(status)
        {
        }

        constexpr      operator i64() const { return StatusCode; }
        constexpr      operator bool() const { return DidFail(); }

        constexpr bool DidFail() const
        {
            auto v = static_cast<__INTPTR_TYPE__>(StatusCode);
            if (static_cast<__UINTPTR_TYPE__>(v) > -4096ul) return -v;
            return 0;
        }

        i64 StatusCode = 0;
    };

    constexpr usize      SYS_WRITE = 1;
    constexpr usize      SYS_MMAP  = 9;
    constexpr usize      SYS_EXIT  = 60;

    static inline Status SyscallAsm0(upointer n)
    {

        Status ret;
        asm volatile(SyscallInvoker
                     : "=a"(ret.StatusCode)
                     : "a"(n)
                     : "rcx", "r11", "memory");
        return ret;
    }

    static inline Status SyscallAsm1(upointer n, upointer a1)
    {
        Status ret;
        asm volatile(SyscallInvoker
                     : "=a"(ret.StatusCode)
                     : "a"(n), "D"(a1)
                     : "rcx", "r11", "memory");
        return ret;
    }

    static inline Status SyscallAsm2(upointer n, upointer a1, upointer a2)
    {
        Status ret;
        asm volatile(SyscallInvoker
                     : "=a"(ret.StatusCode)
                     : "a"(n), "D"(a1), "S"(a2)
                     : "rcx", "r11", "memory");
        return ret;
    }

    static inline Status SyscallAsm3(upointer n, upointer a1, upointer a2,
                                     upointer a3)
    {
        Status ret;
        asm volatile(SyscallInvoker
                     : "=a"(ret.StatusCode)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3)
                     : "rcx", "r11", "memory");
        return ret;
    }

    static inline Status SyscallAsm4(upointer n, upointer a1, upointer a2,
                                     upointer a3, upointer a4)
    {
        Status           ret;
        register upointer r10 asm("r10") = a4;
        asm volatile(SyscallInvoker
                     : "=a"(ret.StatusCode)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10)
                     : "rcx", "r11", "memory");
        return ret;
    }

    static inline Status SyscallAsm5(upointer n, upointer a1, upointer a2,
                                     upointer a3, upointer a4, upointer a5)
    {
        Status           ret;
        register upointer r10 asm("r10") = a4;
        register upointer r8 asm("r8")   = a5;
        asm volatile(SyscallInvoker
                     : "=a"(ret.StatusCode)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
                     : "rcx", "r11", "memory");
        return ret;
    }

    static inline Status SyscallAsm6(upointer n, upointer a1, upointer a2,
                                     upointer a3, upointer a4, upointer a5,
                                     upointer a6)
    {
        Status           ret;
        register upointer r10 asm("r10") = a4;
        register upointer r8 asm("r8")   = a5;
        register upointer r9 asm("r9")   = a6;
        asm volatile(SyscallInvoker
                     : "=a"(ret.StatusCode)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8),
                       "r"(r9)
                     : "rcx", "r11", "memory");
        return ret;
    }

#define GetMacro(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define InvokeSyscall(...)                                                     \
    GetMacro(__VA_ARGS__, SyscallAsm6, SyscallAsm5, SyscallAsm4, SyscallAsm3,  \
             SyscallAsm2, SyscallAsm1, SyscallAsm0)(__VA_ARGS__)

    inline Status DoSyscall(upointer n, upointer a1, upointer a2, upointer a3,
                            upointer a4, upointer a5, upointer a6)
    {
        return InvokeSyscall(n, a1, a2, a3, a4, a5, a6);
    }
    inline Status DoSyscall(upointer n, upointer a1, upointer a2, upointer a3,
                            upointer a4, upointer a5)
    {
        return InvokeSyscall(n, a1, a2, a3, a4, a5);
    }
    inline Status DoSyscall(upointer n, upointer a1, upointer a2, upointer a3,
                            upointer a4)
    {
        return InvokeSyscall(n, a1, a2, a3, a4);
    }
    inline Status DoSyscall(upointer n, upointer a1, upointer a2, upointer a3)
    {
        return InvokeSyscall(n, a1, a2, a3);
    }
    inline Status DoSyscall(upointer n, upointer a1, upointer a2)
    {
        return InvokeSyscall(n, a1, a2);
    }
    inline Status DoSyscall(upointer n, upointer a1)
    {
        return InvokeSyscall(n, a1);
    }
    inline Status DoSyscall(upointer n) { return InvokeSyscall(n); }

    template <typename... Args>
    inline Status Syscall(Args&&... args)
    {
        return DoSyscall(upointer(args)...);
    }
}; // namespace Carbon::InternalAPI
