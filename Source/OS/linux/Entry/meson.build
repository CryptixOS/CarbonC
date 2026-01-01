#*
#* Created by v1tr10l7 on 17.09.2025.
#* Copyright (c) 2025-2025, Szymon Zemke <v1tr10l7@proton.me>
#*
#* SPDX-License-Identifier: GPL-3
#*/

crt = custom_target('crt1',
    build_by_default: true,
    command: c.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
    input: host_machine.cpu_family() / 'crt1.S',
    output: 'crt1.o',
    install: true,
    install_dir: get_option('libdir')
)

crt_pie = custom_target('Scrt1',
    build_by_default: true,
    command: c.cmd_array() + ['-fPIE', '-c', '-o', '@OUTPUT@', '@INPUT@'],
    input: host_machine.cpu_family() / 'Scrt1.S',
    output: 'Scrt1.o',
    install: true,
    install_dir: get_option('libdir')
)

custom_target('crti',
    build_by_default: true,
    command: c.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
    input: host_machine.cpu_family() / 'crti.S',
    output: 'crti.o',
    install: true,
    install_dir: get_option('libdir')
)

custom_target('crtn',
    build_by_default: true,
    command: c.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
    input: host_machine.cpu_family() / 'crtn.S',
    output: 'crtn.o',
    install: true,
    install_dir: get_option('libdir')
)
carbonc_srcs += crt
