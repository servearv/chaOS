.section .init

.option norvc

.type start, @function
.global start


start:
	; .cfi_startproc
	
; .option push
; .option norelax
; 	la gp, global_pointer
; .option pop
	
	/* Reset satp */
	csrw satp, zero
	
	/* Setup stack [sp = stack_top + (mhartid + 1) * 4096]*/
	la sp, stack_top
	li a0, 4096
	csrr a1, mhartid
	addi a1, a1, 1
	mul a1, a1, a0
	add sp, sp, a1

	
	/* Clear the BSS section */
	la t5, bss_start
	la t6, bss_end


bss_clear:
	sd zero, (t5)
	addi t5, t5, 8
	bltu t5, t6, bss_clear
	
	la t0, kmain
	csrw mepc, t0
	
	/* Jump to kernel! */
	tail kmain
	
	; .cfi_endproc

.end
