# https://lowlevel.academy/labs/1
# https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
# https://jameshfisher.com/2018/03/10/linux-assembly-hello-world/

.intel_syntax noprefix
.section .data
  # .asciz means the string ends in a null-byte, or is null terminated
  hello: .asciz "Hello World\n"

.section .text
.global _start

_start:
  # Write syscall
  mov eax, 4
  mov ebx, 1  # file descriptor(stdout)
  lea ecx, [hello] # pointer to the message
  mov edx, 12 # length of the message
  int 0x80 # call kernal

  # Exit syscall
  # Linux assembly syscall number: https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86-32_bit
  mov eax, 1 # mov `1` to `eax`, 1 is the syscall number for exit
  xor ebx, ebx # exit code 0
  int 0x80 # trigger syscall
