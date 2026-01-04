/* Set the entry point of the executable */
ENTRY(_start)

/* Define the memory layout (Simplified for standard user-space binaries) */
SECTIONS
{
    /* 1. Executable Code */
    /* Usually starts at a high address like 0x400000 on x86_64 */
    . = 0x400000;

    .text : {
        *(.text.unlikely .text.*_unlikely .text.exit .text.exit.*)
        *(.text.startup .text.startup.*)
        *(.text .stub .text.* .gnu.linkonce.t.*)
    }

    /* 2. Read-Only Data */
    .rodata : {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    }

    /* 3. Global Constructors (The "Init Array") */
    .init_array : {
        PROVIDE(__init_array_start = .);
        /* Sort by priority if attribute((constructor(pri))) is used */
        KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
        KEEP (*(.init_array .ctors))
        PROVIDE(__init_array_end = .);
    }

    /* 4. Global Destructors (The "Fini Array") */
    .fini_array : {
        PROVIDE(__fini_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
        KEEP (*(.fini_array .dtors))
        PROVIDE(__fini_array_end = .);
    }

    /* 5. Initialized Data (takes up space in the binary file) */
    /* Ensure it's aligned to a page boundary for memory protection */
    . = ALIGN(CONSTANT (MAXPAGESIZE));

    .data : {
        *(.data .data.* .gnu.linkonce.d.*)
    }

    /* 6. Uninitialized Data (Zeroed at runtime, takes 0 bytes in binary) */
    .bss : {
        PROVIDE(__bss_start = .);
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(64 / 8); /* Align to 8 bytes */
        PROVIDE(__bss_end = .);
    }

    /* Define the end of the binary's memory footprint */
    _end = .; 
}
