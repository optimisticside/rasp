; yields the processor until the next interrupt
; can be used for hangning
_halt:
	wfi
	ret

; tries to release a spinlock
_stry:
	mov	r1,#0
	swp	r2,r1
	mov	r0,r1
	ret

; disables interrupts
_cli:
	msr	daifset, #2
	ret

; enables interrupts
_sti:
	msr	daifclr, #2
	ret
