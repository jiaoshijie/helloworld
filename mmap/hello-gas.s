.section .text
.global _start

_start:
  movq $1, %rax
  movq $1, %rdi
  leaq .hello(%rip), %rsi
  movq $12, %rdx
  syscall
  ret

.hello: .asciz "Hello World\n"
