.BB_0:
.global func
func:
  pushq %rbp
  movq %rsp, %rbp
  jmp .func
.func:
  movl $2, -8(%rbp)
  movl -8(%rbp), %eax
  movl %eax, -4(%rbp)
  movl -4(%rbp), %eax
  jmp .BB_1
.BB_1:
  popq %rbp
  ret
.BB_2:
.global f
f:
  pushq %rbp
  movq %rsp, %rbp
  jmp .f
.f:
  jmp .BB_3
.BB_3:
  popq %rbp
  ret
.BB_4:
.global main
main:
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp
  jmp .main
.main:
  movl $65, -12(%rbp)
  movl -12(%rbp), %ebx
  movl %ebx, -4(%rbp)
  call func
  movl %eax, -16(%rbp)
  movl %eax, -8(%rbp)
  call getchar
  movl %eax, -20(%rbp)
  movl %eax, -32(%rbp)
  movl -32(%rbp), %edi
  call putchar
  movl %eax, -24(%rbp)
  movl $0, -28(%rbp)
  movl -28(%rbp), %eax
  jmp .BB_5
.BB_5:
  leave
  ret
