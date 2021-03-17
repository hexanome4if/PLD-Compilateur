.globl main
 main:
   pushq %rbp
   movq %rsp, %rbp
   movl $42, -4(%rbp)
   movl $36, -8(%rbp)
   movl $0, -12(%rbp)
   movl $0, -16(%rbp)
   movl $0, -20(%rbp)
   movl -4(%rbp), %eax
   movl %eax, -8(%rbp)
   movl $2, -24(%rbp)
   movl -24(%rbp), %eax
   movl %eax, -4(%rbp)
   movl	-4(%rbp), %edx
   movl	-8(%rbp), %eax
   addl	%edx, %eax
   movl	%eax, -28(%rbp)
   movl -28(%rbp), %eax
   movl %eax, -12(%rbp)
   movl -12(%rbp), %eax
   popq %rbp
   ret
