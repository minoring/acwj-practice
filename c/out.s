	.text
.LC0:
	.string	"%d\n"
printint:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	_printf
	nop
	leave
	ret

	.comm	i,8,8
	.text
	.global	_main
_main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$1, %r8
	movq	%r8, i(%rip)
L1:
	movq	i(%rip), %r8
	movq	$10, %r9
	cmpq	%r9, %r8
	jg	L2
	movq	i(%rip), %r8
	movq	%r8, %rdi
	call	printint
	movq	i(%rip), %r8
	movq	$1, %r9
	addq	%r8, %r9
	movq	%r9, i(%rip)
	jmp	L1
L2:
	movl $0, %eax
	popq   %rbp
	ret
	.comm	a,8,8
	.comm	b,8,8
	.text
	.global	_fred
_fred:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$12, %r8
	movq	%r8, a(%rip)
	movq	$3, %r8
	movq	a(%rip), %r9
	imulq	%r8, %r9
	movq	%r9, b(%rip)
	movq	a(%rip), %r8
	movq	b(%rip), %r9
	cmpq	%r9, %r8
	jl	L3
	movq	$2, %r8
	movq	b(%rip), %r9
	imulq	%r8, %r9
	movq	a(%rip), %r8
	subq	%r8, %r9
	movq	%r9, %rdi
	call	printint
L3:
	movl $0, %eax
	popq   %rbp
	ret
