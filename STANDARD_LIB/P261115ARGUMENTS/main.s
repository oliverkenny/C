	.section	.rodata
	.align 8
.LC0:
	.string	"Expected arguments: %i  Actual arguments: %i\n"
.LC1:
	.string	"Executed incorrectly."
.LC2:
	.string	"Arguments: "
.LC3:
	.string	"%s "
.LC4:
	.string	"Executed correctly."
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$2, -20(%rbp)
	je	.L2
	movl	-20(%rbp), %eax
	movl	%eax, %edx
	movl	$2, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %edi
	call	puts
	jmp	.L3
.L2:
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$1, -4(%rbp)
	jmp	.L4
.L5:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L4:
	cmpl	$1, -4(%rbp)
	jle	.L5
	movl	$10, %edi
	call	putchar
	movl	$.LC4, %edi
	call	puts
.L3:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 5.2.0"
	.section	.note.GNU-stack,"",@progbits
