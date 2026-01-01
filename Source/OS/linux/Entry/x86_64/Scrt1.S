.section .text
.global _start
_start:
	mov %rsp, %rdi
	lea main(%rip), %rsi
	call __carbon_entry
.section .note.GNU-stack,"",%progbits

