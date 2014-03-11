	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb

.global fork
fork:
	push {r8}
	mov r8, #0x1
	svc 0
	nop
	pop {r8}
	bx lr
.global getpid
getpid:
	push {r8}
	mov r8, #0x2
	svc 0
	nop
	pop {r8}
	bx lr
.global write
write:
	push {r8}
	mov r8, #0x3
	svc 0
	nop
	pop {r8}
	bx lr
.global read
read:
	push {r8}
	mov r8, #0x4
	svc 0
	nop
	pop {r8}
	bx lr
.global interrupt_wait
interrupt_wait:
	push {r8}
	mov r8, #0x5
	svc 0
	nop
	pop {r8}
	bx lr
.global getpriority
getpriority:
	push {r8}
	mov r8, #0x6
	svc 0
	nop
	pop {r8}
	bx lr
.global setpriority
setpriority:
	push {r8}
	mov r8, #0x7
	svc 0
	nop
	pop {r8}
	bx lr
.global mknod
mknod:
	push {r8}
	mov r8, #0x8
	svc 0
	nop
	pop {r8}
	bx lr
.global sleep
sleep:
	push {r8}
	mov r8, #0x9
	svc 0
	nop
	pop {r8}
	bx lr
