# Kernelcon-2020-virtualmachine

## TODO

1. strip the math opperators out
2. add an shl opperator
3. add a shr opperator
4. fix the INT_ to opperate off the interupt tasble
5. set permissions on interupt table locations 0x100-103 on the vdisk
6. write an opcode map to make programming challenges easier in hex

## OP-CODE map
~~~~
program execution starts at org 0x7c00 
boot sector goes to 0x7c80 bytes 

interupt table starts at offset 0x100
default interupts:
  int 1 ~ address 0x100
          keyboard buffer, reads data from the keyboard to a small data segment 
          
  int 2 ~ address 0x101 
          Srial bus: reads hard disk drive NOT COMPLEATE
  int 2 ~ address 0x102
          BIOS video outpu, when called prints the character stored in DI to the sacreen.
          this may be modified to allow for string output as well 
          
op-code format
  5 bits for opcode
  3 bits for flag composition
  

  mov  0b00111xxx
  ~~~~ 
  
  As you go through the program please update opcodes!
