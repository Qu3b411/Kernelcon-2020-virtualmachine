the echo OS.VKDSK will be used to test the opcode changes that will be occuring in the software

currently the op-code works and one may run echo, but one mayu not create a calling convention without 
the soon to be occuring drastic changes. these changes may look minor but they have major reprocussions 
on individuals using jmp in their software package
~~~~
org 0x7c00

mov cx,0  	  ;3B 00 00 06 00 00 00 00 
mov sp,1200 	;3B 00 00 0C 00 00 12 00 
mov cs,1201	  ;3B 00 00 08 00 00 12 01 
nop		        ;00 00 00 00 00 00 00 00 
nop		        ;00 00 00 00 00 00 00 00 
nop 		      ;00 00 00 00 00 00 00 00 
mov bx, 0Eh 	;3B 00 00 02 00 00 00 0E 
iqrl ax		    ;63 00 00 01 00 00 00 00 
iqrl cx		    ;63 00 00 03 00 00 00 00 
push ax		    ;29 00 00 01 00 00 00 00 
and ax,bx	    ;69 00 00 01 00 00 00 02 
mov dx,ax	    ;39 00 00 04 00 00 00 01 
pop ax		    ;30 00 00 01 00 00 00 00 
xor ax,bx	    ;79 00 00 01 00 00 00 02 
shl dx,1	    ;0B 00 00 04 00 00 00 01 
mov bx,dx	    ;39 00 00 02 00 00 00 04 
cmp bx,0	    ;4B 00 00 02 00 00 00 00 
jnz cx		    ;5F 00 1F 10 00 00 00 00 ->59 00 00 07 00 00 00 03 
push ax		    ;29 00 00 01 00 00 00 00 
jmp 11E0h	    ;59 00 04 78 00 00 00 00 ->5B 00 00 01 00 00 11 E0

org 0x1200

mov DI,65h	  ;3B 00 00 05 00 00 00 65
int 2		      ;40 00 00 02 00 00 00 00
mov DI,63h	  ;3B 00 00 05 00 00 00 63
int 2		      ;40 00 00 02 00 00 00 00
mov DI,68h	  ;3B 00 00 05 00 00 00 68
int 2		      ;40 00 00 02 00 00 00 00
mov DI,6Fh	  ;3B 00 00 05 00 00 00 6F 
int 2		      ;40 00 00 02 00 00 00 00 
mov DI,20h	  ;3B 00 00 05 00 00 00 20 
int 2		      ;40 00 00 02 00 00 00 00 
nop		        ;00 00 00 00 00 00 00 00 
nop		        ;00 00 00 00 00 00 00 00 
int 1		      ;40 00 00 01 00 00 00 00 
mov AX,5	    ;3B 00 00 01 00 00 00 05 
shl AX,1	    ;0B 00 00 01 00 00 00 01 
cmp AX,DI	    ;49 00 00 01 00 00 00 05 
int 2 		    ;40 00 00 02 00 00 00 00 
jmp 1250h	    ;5F 00 04 94 00 00 00 00 ->5b 00 00 01 00 00 12 50
~~~~
