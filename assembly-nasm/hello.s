;; https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
;; https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md
;; https://www.nasm.us/doc/nasmdoc0.html

%define SYS_WRITE 1
%define SYS_EXIT 60
%define STDOUT 1

global _start

segment .text
_start:
  ;; write
  mov rax, SYS_WRITE
  mov rdi, STDOUT
  lea rsi, [rel hello]
  mov rdx, hello_size
  syscall

  ;; exit
  mov rax, SYS_EXIT
  mov rdi, 0
  syscall

segment .data
  hello: db "Hello, World", 10
  hello_size: equ $-hello
