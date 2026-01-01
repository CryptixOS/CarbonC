#*
#* Created by v1tr10l7 on 13.07.2025.
#* Copyright (c) 2025-2025, Szymon Zemke <v1tr10l7@proton.me>
#*
#* SPDX-License-Identifier: GPL-3
#*/
project('carbonc', ['c', 'cpp'],
  version: 'v0.0.1', license: 'GPL-3.0',
  default_options: [
    'optimization=3',
    'warning_level=2',
    'werror=true',
    'wrap_mode=forcefallback',
    'b_lundef=false',
    'b_pie=true',
    'c_std=c17',
    'cpp_std=c++23',
  ],
)

if not meson.get_compiler('cpp').has_argument('-std=gnu++23')
  error('C++23 support is needed. Please install clang 17 or higher.')
endif

c = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')
ld = cxx.get_linker_id()
arch = host_machine.cpu_family()
qemulog = meson.project_source_root() / 'qemu.log'

carbonc_srcs = []

include_directories = [
  include_directories('Source'),
]

# ==============================================================================
### Compiler arguments
warnings = [
  #'-Wno-error=#warnings',
  '-Wno-builtin-macro-redefined',
  '-Wno-macro-redefined',
  '-Wno-nan-infinity-disabled',
  '-Wno-deprecated-builtins',
  '-Wno-unused-parameter',
  '-Wno-frame-address',
  '-Wno-c23-extensions',
]

macros = [
    '-DFMT_HEADER_ONLY',
    '-DFMT_STATIC_THOUSANDS_SEPARATOR=1',
    '-DFMT_USE_LONG_DOUBLE=0',
    '-DFMT_USE_DOUBLE=0',
    '-DFMT_USE_FLOAT=0',
    '-DFMT_USE_FLOAT128=0',
    '-DFMT_EXCEPTIONS=0',
    '-DLIMINE_API_REVISION=3',
    '-DMAGIC_ENUM_NO_STREAMS=1',
    '-DMAGIC_ENUM_RANGE_MAX=0x8a00',
    '-DPRISM_BUILD_DEBUG=1',
    '-DPRISM_LOG_ENABLE=1',
    '-DPRISM_TARGET_CRYPTIX=0',
    '-DPRISM_TARGET_CARBONC=1',
    #'-DPRISM_DISABLE_FMT=1',
    '-DUACPI_FORMATTED_LOGGING',
    '-DFMT_BUILTIN_TYPES=0',
    '-D_LIBCPP_HAS_NO_THREADS',
]

add_global_arguments(
  [
    warnings,
    macros,
    '-ffreestanding',
    # keep stack pointer in the appropriate register
    '-fno-omit-frame-pointer',
    '-fno-lto',
    # '-fsanitize=undefined',
    '-fno-stack-protector',
    # '-fstack-protector-all',
    # '-mstack-protector-guard=global',
    '-fno-PIC',
    '-fPIE',
    '-nostdlib',
    '-static',
    '-I' + meson.project_source_root() / 'Source' / 'OS' / 'generic' / 'include',
  ],
  language: ['c', 'cpp'],
)

add_global_arguments(
  [
    # pass the size argument to delete operator
    '-fsized-deallocation',
    '-D__cplusplus=202302L',
    '-MP',
    '-fno-exceptions',
    '-fno-rtti',
    '-Wno-non-virtual-dtor',
    '-nostdinc++',
    '-masm=intel'
  ],
  language: 'cpp',
)

cxx_args = []
ld_args = [
  '-nostdlib',
  '-static'
]

incs = []
incs += include_directories('Source', 'Prism/Source')
subdir('Source')

# ==============================================================================
### Dependencies
#prism = subproject('prism', default_options: 'extra_incs=' +
#    meson.project_source_root() / 'Source/OS/generic/include')
deps = [
  # prism.get_variable('prism_dep')
  #dependency(
  #  'compiler_rt_builtins',
  #  default_options: 'custom_includes=' + 
  #    meson.project_source_root() / 'Kernel/Library/KLibC',
  #),
  # dependency('demangler'),
  dependency('fmt10'),
  dependency('freestnd-cxx-hdrs'),
  dependency('string'),
  # dependency('magic_enum', default_options: [
  #   'test=false',
  # ]),
]

inc_deps = [ ]
foreach dep : deps
    inc_deps += dep.partial_dependency(includes : true)
endforeach
# subdir('Prism/Source')

# ==============================================================================


# ==============================================================================
### Targets

pkgconfig = import('pkgconfig')
carbonc = static_library(
  'carbonc',
  carbonc_srcs, cpp_args: cxx_args,
  include_directories: incs,
  dependencies: deps,
  link_args: [ld_args, '-Wl,--unresolved-symbols=ignore-in-object-files'],
  install: false,
)

carbonc_dep = declare_dependency(
  include_directories: incs,
  compile_args: cxx_args,
  dependencies: deps,
)
dep = declare_dependency(
  compile_args: cxx_args,
  include_directories: incs,
  dependencies: carbonc_dep,
  link_with: carbonc,
)

subdir('Sandbox')
sandbox = executable(
  'sandbox', sandbox_srcs,
  include_directories: incs,
  dependencies: deps,
  link_args: [ld_args, '-Wl,--entry=_start'],
  link_with: carbonc,
  install: false,
)
