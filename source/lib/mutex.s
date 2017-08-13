.global lock_mutex
.global unlock_mutex

lock_mutex:
    ldr r1, =#2
1:
    ldrex r2, [r0]
    cmp r2, r1
    beq 2f
    strex r2, r1, [r0]
    cmp r2, #1
    beq 1b
    bx lr
2:
    wfe
    b 1b

unlock_mutex:
    ldr r1, =#0
    str r1, [r0]
    sev
    bx lr
