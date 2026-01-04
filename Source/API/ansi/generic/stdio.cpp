/*
 * Created by v1tr10l7 on 04.01.2026.
 * Copyright (c) 2024-2026, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Prism/Debug/Log.hpp>
#include <stdio.h>

extern "C"
{
    FILE* stdin  = nullptr;
    FILE* stdout = nullptr;
    FILE* stderr = nullptr;

    using namespace Prism;
    int vfprintf(FILE* stream, char const* fmt, va_list ap)
    {
        return Log::Logv(LogLevel::eNone, fmt, *reinterpret_cast<VaList*>(&ap));
    }
    int fprintf(FILE* stream, char const* fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        int ret = vfprintf(stream, fmt, ap);
        va_end(ap);
        return ret;
    }
};
