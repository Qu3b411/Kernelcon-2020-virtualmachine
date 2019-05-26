This disk represents a hypothetical architecture, 
their are 0x200 bytes in total one may use to boot this disk, addresses 7c00h to 7e00h, the program will terminate at 7e00h, the following
is the best manner to boot the disk and get to the second stage

~~~~
;entry point 

org 7c00h

;the interupt table occures between 100h and 300h, 
;this boot will allocate 0xf00 bytes, the stack can theirfore be 
;placed at offset 1200h their is normally a base pointer, that has been removed 
;this is to cause mayham and problems if the stack is poped incorrectly by contestentes

mov sp, 1200h       ;3b 00 00 0c 00 00 12 00

;cs is the code segment pointer it should be placed directly after the stacks placement
;it is irrelevent, but would have been used if time permitted to make the mechanims to do 
;memory protection and permissions, this was the oriiginal plan, but time would not permit for
;the development and testing of the rich feature set this would bring, however it is still possible
;to set the code segment pointer.

mov cs,1201h        ;3b 00 00 08 00 00 12 01

;place a division between functional components within the boot sector

nop                 ;00 00 00 00 00 00 00 00 
nop                 ;00 00 00 00 00 00 00 00
nop                 ;00 00 00 00 00 00 00 00

;call the main function of the program, in a normal environment this would be the stage 2 
;boot to load the kernel

;the of calling another function are as follows

;the call takes 18h instructions to complete, padd the end with nops

mov bx,20h            ;3b 00 00 02 00 00 00 20

;get the current program offset

iqrl ax               ;63 00 00 01 00 00 00 00

; add the offset to ax

iqrl ax		            ;63 00 00 01 00 00 00 00 
iqrl cx		            ;63 00 00 03 00 00 00 00 
push ax		            ;29 00 00 01 00 00 00 00 
and ax,bx	            ;69 00 00 01 00 00 00 02 
mov dx,ax	            ;39 00 00 04 00 00 00 01 
pop ax		            ;30 00 00 01 00 00 00 00 
xor ax,bx	            ;79 00 00 01 00 00 00 02 
shl dx,1	            ;0B 00 00 04 00 00 00 01 
mov bx,dx	            ;39 00 00 02 00 00 00 04 
cmp bx,0	            ;4B 00 00 02 00 00 00 00 
jnz cx		            ;59 00 00 07 00 00 00 03 

;store the return address on the stack

push ax               ;29 00 00 01 00 00 00 00 

; put the main function nere the bottem of the code segment 
;and work towards the boot sector

jmp 1250h	            ;5B 00 00 01 00 00 12 50

