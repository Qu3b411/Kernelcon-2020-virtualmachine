# Solution

~~~~
1. program execution starts at 0x7c00

2. The op-code for this vm is comprised of 5 bits and has a 3 bit flag proceeding it

                  the first 1 bits of the flag determine if one is affecting a register, or a memory address!
                  
                        0b1 indicates one is affecting the value of a memory address!
                        0b0 indicates one is affecting the value of a register!
                        
                 the last 2 bits of the flag indicate that the unaffected value influencing this instruction is a memory address, 
                 register, or constant
                  
                        0b10 indicates the source value is a memory address
                        0b01 indicates the source value is a register 
                        0b11 indicates the source value is a constant
                        
  the following 24 bits are used to store the first opperand, and the remaining  32 bits to store the second opperand
                   

3. The interupt table starts at address 0x100, ends at address 0x300, and contains 3 bus addresses by default, 
       video out 0x102
       keyboard in 0x100
       disk in 0x101
      
4.  the mov instruction has the following op-code  0b00111
5.  the and instruction has the following op-code  0b01101
6.  the shl instruction has the following op-code  0b00001
7.  the shr instruction has the following op-code  0b00010
8.  the push instruction has the following op-code 0b00101
9.  the pop instruction has the following op-code  0b00110
10. the int instruction has the following op-code  0b01000
11. the nop instruction has the following op-code  0b00000
12. the cmp instruction has the following op-code  0b01001
13. the iqrl instruction has the following op-code 0b01100
14. the relative jmp instruction has the following op-code 0b01010
15. the far jmp instruction has the following op-code 0b01011
16. the or instruction has the following op-code 0b01110
17. the xor instruction has the following op-code 0b01111
18. the not instruction has the following op-code 0b10000

19. their are 12 registers give the opcode to refer to each one

AX: 0b0001   BX: 0b0010      CX: 0b0011    DX:  0b0100
SP: 0b1100   SI: 0b0110      DI:  0b0101   SS:  0b1001
DS: 0b0111   CS: 0b1000      ES: 0b1010    IP:  0b1011

20  write the opcode for the following  in hex notation

        mov ax,0xdeadbeaf : EB 00 00 01 DE AD BE AF
        
        push ax           : 29 00 00 01 00 00 00 00
        
        pop bx            : 30 00 00 02 00 00 00 00
        
        shl bx,5          : 0B 00 00 02 00 00 00 05
        
        xor ax,bx         : 79 00 00 01 00 00 00 02
        
        what would the value of ax be if these instructions were run 
        0xB1A6B4F
        
if you completed this task you are ready to start the next challenge.
~~~~
