.section .text
.global _start
_start:
	mov %rsp, %rdi
	mov $main, %rsi
	call __carbon_entry
.section .note.GNU-stack,"",%progbits

