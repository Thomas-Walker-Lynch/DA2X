	.file	"goto_and_stack.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"%d"
.LC3:
	.string	"finishing %d"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	movabsq	$-4294967296, %r11
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	%edi, %r12d
	movabsq	$4294967296, %rax
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movabsq	$-4294967296, %rbx
	addq	%r11, %rsp
	.cfi_def_cfa_offset 4294967328
	movdqa	.LC0(%rip), %xmm0
	addq	%rsp, %rax
	addq	%rax, %rbx
	leaq	512(%rbx), %rbp
	movq	%rbx, %rax
	.p2align 4,,10
	.p2align 3
.L2:
	movdqa	%xmm0, %xmm1
	addq	$16, %rax
	paddd	.LC1(%rip), %xmm0
	movaps	%xmm1, -16(%rax)
	cmpq	%rbp, %rax
	jne	.L2
	cmpl	$2, %r12d
	je	.L4
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%rbx), %esi
	movl	$.LC2, %edi
	xorl	%eax, %eax
	addq	$4, %rbx
	call	printf
	movl	$10, %edi
	call	putchar
	cmpq	%rbp, %rbx
	jne	.L3
	movabsq	$4294967296, %rax
	movdqa	.LC0(%rip), %xmm1
	movabsq	$-4294967296, %rbx
	addq	%rsp, %rax
	addq	%rax, %rbx
	leaq	512(%rbx), %rbp
	movq	%rbx, %rax
	.p2align 4,,10
	.p2align 3
.L5:
	movdqa	%xmm1, %xmm0
	addq	$16, %rax
	paddd	.LC1(%rip), %xmm1
	pslld	$1, %xmm0
	movaps	%xmm0, -16(%rax)
	cmpq	%rbp, %rax
	jne	.L5
	.p2align 4,,10
	.p2align 3
.L6:
	movl	(%rbx), %esi
	movl	$.LC2, %edi
	xorl	%eax, %eax
	addq	$4, %rbx
	call	printf
	movl	$10, %edi
	call	putchar
	cmpq	%rbp, %rbx
	jne	.L6
	movabsq	$4294967296, %rax
	movdqa	.LC0(%rip), %xmm1
	movabsq	$-4294967296, %rbx
	addq	%rsp, %rax
	addq	%rax, %rbx
	leaq	512(%rbx), %rbp
	movq	%rbx, %rax
	.p2align 4,,10
	.p2align 3
.L7:
	movdqa	%xmm1, %xmm0
	addq	$16, %rax
	paddd	.LC1(%rip), %xmm1
	pslld	$1, %xmm0
	movaps	%xmm0, -16(%rax)
	cmpq	%rax, %rbp
	jne	.L7
	.p2align 4,,10
	.p2align 3
.L8:
	movl	(%rbx), %esi
	movl	$.LC2, %edi
	xorl	%eax, %eax
	addq	$4, %rbx
	call	printf
	movl	$10, %edi
	call	putchar
	cmpq	%rbx, %rbp
	jne	.L8
	movl	$5, %esi
	movl	$.LC2, %edi
	xorl	%eax, %eax
	call	printf
.L4:
	movl	$5, %esi
	movl	$.LC3, %edi
	xorl	%eax, %eax
	call	printf
	movl	%r12d, %eax
	movabsq	$4294967296, %r11
	addq	%r11, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC1:
	.long	4
	.long	4
	.long	4
	.long	4
	.ident	"GCC: (GNU) 10.2.1 20200723 (Red Hat 10.2.1-1)"
	.section	.note.GNU-stack,"",@progbits
