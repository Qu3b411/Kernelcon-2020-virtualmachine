# Kernelcon-2020-virtualmachine

## TODO

~~1. strip the math opperators out~~

~~2. add an shl opperator~~

3. add a shr opperator
4. fix the INT_ to opperate off the interupt tasble
5. set permissions on interupt table locations 0x100-103 on the vdisk
6. write an opcode map to make reversing challenges easier for us to write

**once the virtual machine is written and tested their will be 5 challenges in total, 2 programming challenges, they should not be easy and each os.vdsk should work when submited. 2 reverse engineering challenges, and the first challenge will be for contestents to find the opcode set! this is not ment to be an easy catagory**
the virtual machine will live in the root directory,
their will be no OS.VKSK in the root once the vm is finalized. this is just a testing platform.
taikie the time to document the opcodes in the readme. please take time to fix things as you move forward, i know it is going to be dificult but once its done we should have an extreamly nice ctf catagory that makes an impression

## OP-CODE map
~~~~
program execution starts at org 0x7c00 
boot sector goes to 0x7c80 bytes 

    
op-code format
  5 bits for opcode
  3 bits for flag composition
  
  nop  0b00000xxx
  
  shl  0b00001xxx
      shift left instruction
        
  shr  0b00010xxx 
      shift right instruction
        
  invalid instruction  0b00011xxx, enters a processor lock state, infinate loop
       
  invalid instruction  0b00100xxx, enters a processor lock state, infinate loop
           
  push 0b00101xxx 
        pushes an item onto the stack, the stack must be set up by the OS.VDSK
        
  pop  0b00110xxx
        poips from the stack, the stack must have been initilized from the OS.VDSK 
  
  mov  0b00111xxx
  
  int  0b01000xxx 
        calls an interupt function off of the interupt table, the virtual hardware 
        interupts are set up for you by the program. other interupts may take additional work
        andd require you to write your own calling convention.
    
    interupt table starts at offset 0x100
    
    default interupts:
      int 1 ~ address 0x100
              keyboard buffer, reads data from the keyboard to a small data segment 

      int 2 ~ address 0x101 
              Srial bus: reads hard disk drive NOT COMPLEATE
      int 2 ~ address 0x102
              BIOS video outpu, when called prints the character stored in DI to the sacreen.
              this may be modified to allow for string output as well 

  
  cmp  0b01001xxx
        sets the flag register based on comparisons, flags effect jmp adversley
        
  jmp  0b01010xxx
        relative jump
    
  jmpf 0b01011xxx
        far jump
        
  iqrl 0b01100xxx
     instruction query location
     
  and  0b01101xxx
        
  or   0b01110xxx
  
  xor  0b01111xxx
  
  not  0b10000xxx
  
  
  invalid instruction  0b10001xxx, enters a processor lock state, infinate loop
          
  ~~~~ 
  
  As you go through the program please update opcodes!
  
  all math opperators will be removed for my own entertainment while contestants do the ctf 
