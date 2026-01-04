/*
 * Created by v1tr10l7 on 13.07.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <Carbon/Core/Assertions.hpp>
#include <Carbon/Core/CarbonC.hpp>
#include <Carbon/Core/Types.hpp>
#include <Carbon/Platform/posix/Sysdeps.hpp>
#include <string.h>

namespace Carbon
{
    extern "C"
    {
        i32                main(i32 argc, char** argv);

        const char         EXIT_MESSAGE[]      = "LibC: Exiting...\n";
        unsigned long long EXIT_MESSAGE_LENGTH = sizeof(EXIT_MESSAGE);

        enum class AuxiliaryValueType
        {
            eNull                   = 0,
            eIgnore                 = 1,
            eProgramFd              = 2,
            eProgramHeaders         = 3,
            eProgramHeaderEntrySize = 4,
            eProgramHeaderCount     = 5,
            ePageSize               = 6,
            eInterpreterBase        = 7,
            eFlags                  = 8,
            eEntry                  = 9,
            eNotElf                 = 10,
            eUserID                 = 11,
            eEffectiveUserID        = 12,
            eGroupID                = 13,
            eEffectiveGroupID       = 14,
            ePlatform               = 15,
            eHwCap                  = 16,
            eClkTck                 = 17,
            eSecure                 = 23,
            eBasePlatform           = 24,
            eRandom                 = 25,
            eHwCap2                 = 26,
            eExecutablePath         = 31,
            eExeBase                = 32,
            eExeSize                = 33,
        };
        struct AuxiliaryValue
        {
            AuxiliaryValueType Type;
            upointer           Value;
        };

        __attribute__((visibility("default"))) void
        __carbon_entry(upointer* stack)
        {
            i32    argc = static_cast<i32>(stack[0]);
            char** argv = reinterpret_cast<char**>(&stack[1]);

            using namespace Sysdeps;
            for (isize i = 0; i < argc; i++) Write(0, argv[i], strlen(argv[i]));

            // Skip argv
            upointer i    = 1 + argc + 1; // +1 for NULL
            char**   envp = reinterpret_cast<char**>(&stack[i]);

            auto     env  = envp;
            while (*env)
            {
                Write(0, *env, strlen(*env));
                ++env;
            }

            // Skip envp
            while (stack[i] != 0) i++;

            i++; // skip NULL
            AuxiliaryValue* auxv = reinterpret_cast<AuxiliaryValue*>(&stack[i]);

            // Parse auxv if needed
            for (auto* a = auxv; a->Type != AuxiliaryValueType::eNull; a++)
            {
                switch (a->Type)
                {
                    case AuxiliaryValueType::ePageSize:
                        /* store page size */
                        break;
                    case AuxiliaryValueType::eRandom:
                        /* entropy */
                        break;

                    default: break;
                }
            }

            Assert(InitializeLibrary());
            i32 status = main(0, nullptr);
            if (argc > 0) Write(0, argv[0], 5);
            if (argc > 1) Write(0, argv[1], 5);

            // for (usize i = 0; i < 10; i++) PM_UNUSED
            isize nwritten = Write(0, EXIT_MESSAGE, EXIT_MESSAGE_LENGTH);
            IgnoreUnused(nwritten);

            // ShutdownLibrary();
            Exit(status);
        }
    }
}; // namespace Carbon
