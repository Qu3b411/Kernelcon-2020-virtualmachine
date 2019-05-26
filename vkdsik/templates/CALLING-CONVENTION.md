this is the assembly instructions needed to call a program with binary 

~~~~
;save the registers state
;AX will be returned
push BX     ;29 00 00 02 00 00 00 00
push CX     ;29 00 00 03 00 00 00 00
push DX     ;29 00 00 04 00 00 00 00

;store the jmp offset in bx
;0x18 for this function call 

mov BX, 18h  ;3b 00 00 02 00 00 00 18

;store the current instruction pointer offset to ax

iqrl ax     ;63 00 00 01 00 00 00 00

;increment one instruction and store the
;instruction pointers current location to CX

;ADDITION 

iqrl cx       ;63 00 00 03 00 00 00 00
push ax       ;29 00 00 01 00 00 00 00
and ax,bx     ;69 00 00 01 00 00 00 02
mov dx,ax     ;39 00 00 04 00 00 00 01
pop ax        ;30 00 00 01 00 00 00 00
xor ax,bx     ;79 00 00 01 00 00 00 02
shl dx,1      ;0b 00 00 04 00 00 00 01
mov bx,dx     ;39 00 00 02 00 00 00 04
cmp bx,0      ;48 00 00 02 00 00 00 00
jnz cx        ;59 00 00 07 00 00 00 03

;Finish Addition algorithm
;push the returning location onto the stack

push ax       ;29 00 00 01 00 00 00 00

;jmp to function call offset, 0x1200 is an example

jmp 1200h     ;5b 00 00 01 00 00 11 e0
nop           ;00 00 00 00 00 00 00 00

;restore the registers to their initial state

pop dx        ;30 00 00 04 00 00 00 00
pop cx        ;30 00 00 03 00 00 00 00
pop bx        ;30 00 00 02 00 00 00 00
~~~~

returning from a function call is simple, as long as the stack is properly maintained 

~~~~

;retrive the return address from the stack, store it in a non-return register

pop cx        ;30 00 00 03 00 00 00 00

;jmp to cx

jmp cx        ;59 00 00 01 00 00 00 03

~~~~
