/**
 this program utilizes a 64 bit wide field for command syntax and 32bit wide variables
 all op code follows the basic layout specified here ;

    the first 5 bits of all oppcode represent the command to be executed, this means
    that in total their can be 32 commands

        x x x x x * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    the next 3 bits are for argument descriptors, for witch their are 2 descriptors
        * * * * * x * *  -- flag for first argument this will be refer'd to as f1
        * * * * * * x x  -- flag for second argument this will be refer'd to as f2
    the following 24 bits have 2 potential outcomes,
        if f1 is set to 1 then we will be indexing an arbitrary memory address in which case the opcode
        will be as follows

        * * * * * 1 * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 x x x x * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

        else if f1 is set to 0  we are accessing an arbitrary register.

        * * * * * 0 * * x x x x x x x x x x x x x x x x x x x x x x x x * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
29-367
        this address refers to an integer type and can be used to access memory
    the remaining 32 bits can take on one of 3 distinct states
        if f2 is set to 11 then the value of the 32 bit's represents some arbitrary
        constant, in that eventuality the opp-code will
29-367
        * * * * * * 0 1 * * * * * * * * * * * * * * * * * * * * * * * * x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x

        else if f2 is set to 10 then we will be accessing an arbitrary address
            this will appear as follows

         * * * * * * 0 0 * * * * * * * * * * * * * * * * * * * * * * * * 0 0 0 0 0 0 0 0 x x x x x x x x x x x x x x x x x x x x x x x x

        this will be able to access any of the addresses within the virtual memory;

         else if f2 = 01 then we are indexing one of the registers,
         this will appear as follows

         * * * * * * 1 0 * * * * * * * * * * * * * * * * * * * * * * * * 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 x x x x
    all opp-codes portrayed here are in a binary notation, in which 'x' represents the command input area,
    no opp-code within this virtual machine has the ability nor the need to take 2 constant inputs, this is by design
the calculated address space would come to   2^24 addresses each address referring to an integer type of 4 bytes. witch consists of roughly 256MB of memory space.
the remainder was divided into a manor that would accommodate large software projects.

    the virtual computer loads instructions first to the COMMAND_STRUCT witch is an array of instructions to be
    loaded to virtual memory at the CS segment. this COMMAND_STRUCT acts as a virtual hard drive and will store
    128MB worth of data. this could be implemented with a higher memory capacity
*/
#include "VM.h"
/**
* the command struct is loaded from a source such as the harddrive, there is no highly specified
* this struct is loaded from a file and is a manner to store opp-code before it is loaded to the
* virtual memory segment, this also represents a point from which to load software. this is the
* hard drive for this virtual machine.
*/
void nop_(int flag, int a, int b){return;}
/**
 the and instruction takes the and of two inputs and sets it accordingly. this instruction has the
 following OP-CODE specification. the base instruction is 0b01101 and is proceeded by three flag
 bits

    AND -- 0b01101xxx ands two arguments and stores it according to the flag specifications.
           0b011011xx ands data from a source with a memory address. the memory address specified
                      is altered by this OP-CODE.
           0b011010xx and's data from a source with a register. the register specified in load_a
                      is altered by this OP-CODE.
           0b01101x01 ANDs data at a register with the predetermined source. the register is not effected
                      by this OP-CODE.
           0b01101x10 ANDs data at a memory address with a designated source.. the data at the
                      memory address is not affected by this OP-CODE.
           0b01101x11 ANDs data from a designated source with an arbitrary constant.

*/
void and_(int flag, int Load_a, int Load_b){subMacroDef(and,flag,Load_a,Load_b);}
/**
    the or instruction takes two input's and preforms a binary OR's them together. this instruction
    has the following OP-CODE specification. the base instruction is 0b01110 and is proceeded by three
    flag bits.

    OR -- 0b01110xxx OR's takes two arguments and stores them in accordance with the flag bits.
          0b011101xx OR's data from a specified source with data stored with a logical memory address.
                      the data at that specified memory address is altered by this OP-CODE.
          0b011100xx OR'S data from a specified source with a register. the register specified is altered
                     by this OP-CODE.
          0b01110x01 OR's data at a register with the predetermined source. the register is not effected
                      by this OP-CODE.
          0b01110x10 OR's data at a logical memory address with a designated source. the data at the memory
                     address is not effected by this OP-CODE.
          0b01110x11  OR;s data from a designated source with an  arbitrary constant.

*/
void or_(int flag, int Load_a, int Load_b){subMacroDef(or,flag,Load_a,Load_b);}
/**
    the XOR instruction takes two input's and preforms a binary XOR's them together. this instruction
    has the following OP-CODE specification. the base instruction is 0b01111 and is proceeded by three
    flag bits.

    XOR -- 0b01111xxx XOR's takes two arguments and stores them in accordance with the flag bits.
           0b011111xx XOR's data from a specified source with data stored with a logical memory address.
                      the data at that specified memory address is altered by this OP-CODE.
           0b011110xx XOR'S data from a specified source with a register. the register specified is altered
                      by this OP-CODE.
           0b01111x01 XOR's data at a register with the predetermined source. the register is not effected
                      by this OP-CODE.
           0b01111x10 XOR's data at a logical memory address with a designated source. the data at the memory
                      address is not effected by this OP-CODE.
           0b01111x11 XOR's data from a designated source with an  arbitrary constant.

*/
void xor_(int flag, int Load_a, int Load_b){subMacroDef(Xor,flag,Load_a,Load_b);}
void not_(int flag, int Load_a, int setNull){subMacroDef(not,flag,Load_a,setNull);}
/**
    the MOD instruction takes two input's and divides them and then returns the remainder. this instruction
    has the following OP-CODE specification. the base instruction is 0b01110 and is proceeded by three
    flag bits.

    MOD -- 0b01110xxx modulates two arguments and stores them in accordance with the flag bits.
           0b011101xx modulates data from a specified source with data stored with a logical memory address.
                      the data at that specified memory address is altered by this OP-CODE.
           0b011100xx modulates data from a specified source with a register. the register specified is altered
                     by this OP-CODE.
           0b01110x01 modulates data at a register with the predetermined source. the register is not effected
                     by this OP-CODE.
           0b01110x10 modulates data at a logical memory address with a designated source. the data at the memory
                     address is not effected by this OP-CODE.
           0b01110x11 modu data from a designated source with an  arbitrary constant.

*/
void mod_(int flag, int Load_a, int Load_b){subMacroDef(mod,flag,Load_a,Load_b);}
void push_(int flag, int Load,int setNull){paramMacro(push,setNull,Load)SP--;}

/**
    the ADD instruction takes two input's and ADD's them together. this instruction
    has the following OP-CODE specification. the base instruction is 0b01110 and is proceeded by three
    flag bits.

    OR -- 0b01110xxx  adds takes two arguments and stores them in accordance with the flag bits.
          0b011101xx  adds data from a specified source with data stored with a logical memory address.
                      the data at that specified memory address is altered by this OP-CODE.
          0b011100xx  adds data from a specified source with a register. the register specified is altered
                      by this OP-CODE.
          0b01110x01 adds data at a register with the predetermined source. the register is not effected
                      by this OP-CODE.
          0b01110x10 adds data at a logical memory address with a designated source. the data at the memory
                     address is not effected by this OP-CODE.
          0b01110x11  adds data from a designated source with an  arbitrary constant.

*/
void shl_(int flag, int Load_a, int Load_b)
{
    if ((flag == FLAG_REG) ^ (flag == FLAG_CONST))
    {
        subMacroDef(shl,flag,Load_a,Load_b);
    }

}
/**
    the SUB instruction takes two input's and subtracts them to find their difference. this instruction
    has the following OP-CODE specification. the base instruction is 0b01110 and is proceeded by three
    flag bits.

    OR -- 0b01110xxx subtracts two arguments and stores them in accordance with the flag bits.
          0b011101xx subtracts data from a specified source with data stored with a logical memory address.
                      the data at that specified memory address is altered by this OP-CODE.
          0b011100xx subtracts data from a specified source with a register. the register specified is altered
                     by this OP-CODE.
          0b01110x01 subtracts data at a register with the predetermined source. the register is not effected
                      by this OP-CODE.
          0b01110x10 subtracts data at a logical memory address with a designated source. the data at the memory
                     address is not effected by this OP-CODE.
          0b01110x11 subtracts data from a designated source with an  arbitrary constant.

*/
void shr_(int flag, int Load_a, int Load_b)
{
    if ((flag == FLAG_REG) ^ (flag == FLAG_CONST))
    {
        subMacroDef(shr,flag,Load_a,Load_b);
    }
}
/**
    the MULT instruction takes two input's and finds their product. this instruction
    has the following OP-CODE specification. the base instruction is 0b01110 and is proceeded by three
    flag bits.

    MULT -- 0b01110xxx multiplies two arguments and stores them in accordance with the flag bits.
            0b011101xx multiplies data from a specified source with data stored with a logical memory address.
                      the data at that specified memory address is altered by this OP-CODE.
       `    0b011100xx multiplies data from a specified source with a register. the register specified is altered
                     by this OP-CODE.
            0b01110x01 multiplies data at a register with the predetermined source. the register is not effected
                      by this OP-CODE.
            0b01110x10 multiplies data at a logical memory address with a designated source. the data at the memory
                     address is not effected by this OP-CODE.
            0b01110x11 multiplies data from a designated source with an  arbitrary constant.

*/
//void mult_(int flag, int Load_a, int Load_b){subMacroDef(mult,flag,Load_a,Load_b);}
/**
    the DIV instruction takes two input's and divides them. this instruction
    has the following OP-CODE specification. the base instruction is 0b01110 and is proceeded by three
    flag bits.

    DIV -- 0b01110xxx divides two arguments and stores them in accordance with the flag bits.
           0b011101xx divides data from a specified source with data stored with a logical memory address.
                      the data at that specified memory address is altered by this OP-CODE.
           0b011100xx divides data from a specified source with a register. the register specified is altered
                     by this OP-CODE.
           0b01110x01 divides data at a register with the predetermined source. the register is not effected
                     by this OP-CODE.
           0b01110x10 divides data at a logical memory address with a designated source. the data at the memory
                     address is not effected by this OP-CODE.
           0b01110x11 divides data from a designated source with an  arbitrary constant.

*/
//void div_(int flag, int Load_a, int Load_b){subMacroDef(div,flag,Load_a,Load_b);}
/**
    the MOV instruction serves to copy data from a source to a destination. this instruction
    has the oppcode specification 0b00110, and is preceded by 3 flag bits. as specified below

    MOV  -- 0b00001xxx  moves data from the specified flag type to another specified flag type,
                        this implementation uses the following opp-code specifications
            0b000011xx  moves data from a source to a destination memory address.
            0b000010xx  moves data from a source to a destination register
            0b00001x01  moves data from a register to a destination.
            0b00001x10  moves data from a memory address to a destination.
            0b00001x11  moves a predetermined constant to a destination.
    the source buffer being coppied from is unaffected by this instruction.
*/
void mov_(int flag, unsigned int Load_a, unsigned int Load_b)
{
    if (flag&FLAG_H)
    {
        movMacro1(*(RAM_base+Load_a),Load_b);
    }
    else
    {

        switch (Load_a)
        {
            case AX_:movMacro1(AX,Load_b);break;
            case BX_:movMacro1(BX,Load_b);break;
            case CX_:movMacro1(CX,Load_b);break;
            case DX_:movMacro1(DX,Load_b);break;
            default:
            if(FLAGS&kernal)
                {
                    switch(Load_a)
                        case DI_:movMacro1(DI,Load_b);break;
                        case SI_:movMacro2(SI,Load_b);break;
                        case IP_:movMacro2(IP,Load_b);break;
                        case SP_:movMacro2(SP,Load_b);break;
                        case CS_:movMacro2(CS,Load_b);break;
                }
                else{
                    badRegError;
                }
        }
    }
}
/**
 this pops an item from the stack to a register this can be used with function pointers
 if the permission context is properly set from the flags register. if the pop is to the
 instruction pointer an interrupt must be generated to put the code in kernal mode before
 the move occures, this will be an area for serilization to ensure that the function is on the
 stack.
    the pop OP-CODE has the following specification. the initial instruction op-code of 0b00110, with
    no flag parameter set, the flags parameter  should be null.
    the following bits should address one of the registers, general purpose registers can be modified
    without permission escelation. if a pop occures to the instruction pointer then some varification is
    performed. this includes ensuring that the range addressed is greater then the RAM_base and less then
    RAM_base +0x10000000.
*/
void pop_(int flag, int reg, int setnull)
{
     if (SP>RAM_base /*&& SP<BP*/)
     {
        switch (reg)
        {
        case AX_:
            AX = *(++SP);
            break;
        case BX_:
            BX = *(++SP);
            break;
        case CX_:
            CX = *(++SP);
            break;
        case DX_:
            DX = *(++SP);
            break;
        case IP_:
            IP = RAM_base + *(++SP);
        default:

            badRegError;
        }
     }
    else
    {
        printf("Invalid opperation: %s!" ,(SP<=BP ? "this is an empty stack that may not be pop'd":
                                    "insufficient memory"));
        free(RAM_base);
        exit(EXIT_FAILURE);
    }
}

typedef void(*callback)();
void INT_(int flagNull, int interrupt, int setNull)
{
    unsigned long tempfunction;
    switch (interrupt)
    {
        case 0:
            free(RAM_base);
            exit(EXIT_SUCCESS);
        case 1:;
    #ifdef __x86_64
            tempfunction = *(RAM_base+0x101);
            tempfunction <<= 0x20;
            tempfunction ^= *(RAM_base+0x100);
             ((callback)((void(*)(void*))(tempfunction)))();
    #elif __WIN32
           ((callback)((void(*)(long*))*(RAM_base+0x100)))();
    #endif // __x86_64
            break;
        case 2:
        #ifdef __x86_64
            tempfunction = *(RAM_base+0x105);
            tempfunction <<= 0x20;
            tempfunction ^= *(RAM_base+0x104);
            ((callback)((void(*)(void*))(tempfunction)))();
        #elif __WIN32
           ((callback)((void(*)(long*))*(RAM_base+0x104)))();
        #endif // __x86_64
            break;
        default:
            badRegError;
    }
}
/**
    iqrl_ Instruction QueRy Location, sets
    the designated general purpose register
    to the current address of the
    Instruction Pointer by calculating the
    difference between the VM's RAM_base
    and the Instruction pointer, then dividing it
    by 4.
*/
void iqrl_(int flag, int load_a, int setnull)
{
    if(flag == 0b011)
        {
            mov_(flag,load_a,(int)(IP-RAM_base));
        }
        else
        {

            badRegError;
        }
}


void invalid_instruction(int flag,int a, int b)
{
    IP-=1;
}
/**
    relative offset jump instruction . produces a fix for the
    offset and calls the far jump syntax, the fix is produced
    by finding the difference between the IP and the RAM_base.
    then adding the offset* the sizeof(int) in order to get
    the proper offset.
    the flags are the same as the jmpf syntax with only slight
    variations in op-code as specified below.

    this instruction has the following OP-CODE specification
    0b01010 is the base command OP-CODE. it is proceeded by three
    flag bits.

    jmp  -- 0b01010xxx jumps to a relative address if possible.
            0b01010001 makes a relative jump regardless of the state
                    of the FLAGS register.
            0b01010010 makes a relative jump if and only if the less then
                    flag in the FLAGS register is set.
            0b01010011 makes a relative jump if and only if the equal to
                    flag is set in the FLAGS register.
            0b01010100 makes a relative jump if and only if the greater then
                    flag is set in the FLAGS register.
            0b01010101 makes a relative jump if and only if the less then flag
                    or the equal to flag is set in the FLAGS register.
            0b01010110 makes a relative jump if and only if the greater then flag
                    or the equal to flag is set in the FLAGS register
            0b01010111  makes a relative jump if and only if the greater to flag
                    or the less then flags are set in the flag register.
*/
void jmp_(int flag, int flag_2, int offset)
{
    jmpf_(flag,flag_2,(int)((IP-RAM_base)+(offset)));

}
/**
    far jump instruction. takes an offset from the base ram stack and jumps to
    it, the jmp syntax takes a number of flags for conditional operations
    this function relies heavily on the last three bits of the FLAGS. witch
    stores a series of boolean.
    this is a non relative jump function, this is used when the offset of the
    jump being made is known. their is a jmp_ method that handles relative
    offsets. these offsets are fixed and then this method is called with the
    fixed offset.
    this Instruction  has the OP-CODE specification 0b01011 and is proceeded
    by three flag bits

    JMPF -- 0b01011XXX jumps to a specified address if  possible.
            0b01011001 jumps to the designated address regardless of the state of the
                        FLAGS.
            0b01011010 jumps to the designated address if and only if the less then flag
                       in the FLAGS register is set.
            0b01011011 jumps to the designated address if and only if the equal to flag
                        in the FLAGS register is set.
            0b01011100 jumps to the designated address if and only if the greater then
                       flag is set in the FLAGS register.
            0b01011101 jumps to the designated address if either the less then flag or
                        the equal to flags in the FLAGS register.
            0b01011110 jumps to the designated address if either the greater then flag or
                       the equal to flags are set in the FLAGS register.
            0b01011111 jumps to the designated address if either the greater to flag, or the
                        less then flag is set in the FLAGS register.
*/
void jmpf_(int flag, int flag_2, int addr)
{
    switch (flag_2)
    {
        case JMP_flag:
        switch (flag & FLAG_L)\
        {\
            case FLAG_REG:\
                switch (addr)\
                {\
                 /**<  */   case AX_: jmpOpperator(0x00,AX);break;\
                    case BX_: jmpOpperator(0x00,BX);break;\
                    case CX_: jmpOpperator(0x00,CX);break;\
                    case DX_: jmpOpperator(0x00,DX);break;\
                     default:\
                         if(FLAGS&kernal)\
                            {\
                                switch (addr)\
                                {\
                                    case DI_:jmpOpperator(0x00,DI);break;\
                                    case IP_:jmpOpperator(0x00,(int)(IP-RAM_base));break;\
                                    case SI_:jmpOpperator(0x00,(int)(SI-RAM_base));break;\
                                    case CS_:jmpOpperator(0x00,(int)(CS-RAM_base));break;\
                                    case SP_:jmpOpperator(0x00,(int)(SP-RAM_base));break;\
                                    case DS_:jmpOpperator(0x00,(int)(DS-RAM_base));break;\
                                    case ES_:jmpOpperator(0x00,(int)(ES-RAM_base));break;\
                               }\
                            }\
                            else\
                            {\
                                puts("error: bad register index");\
                                exit(EXIT_FAILURE);\
                            }\
                }
                case FLAG_ADDR:\
                    jmpOpperator(0x00,*(RAM_base+addr))\
                    break;\
                case FLAG_CONST:\
                    jmpOpperator(0x00,addr)\
                    break;\
                default:\
                    puts("error: invalid syntax flag not valid");\
                    exit(EXIT_FAILURE);\
            }


           // paramMacro(jmp,0x00,addr)
           /*     if ((RAM_base+addr > RAM_base) && RAM_base+addr<RAM_base+0x1000000)
                IP = RAM_base+addr;*/
            break;
        case JL_flag:
            if (FLAGS&Lt)
                jmpf_(flag,JMP_flag,addr);
            break;
        case JE_flag:
            if (FLAGS&Eq)
                jmpf_(flag,JMP_flag,addr);
            break;
        case JG_flag:
            if (FLAGS&Gt)
                jmpf_(flag,JMP_flag,addr);
            break;
        case JLE_flag:
            if(FLAGS&Lz)
                jmpf_(flag,JMP_flag,addr);
            break;
        case JGE_flag:
            if(FLAGS&Gz)
                jmpf_(flag,JMP_flag,addr);
            break;
        case JNE_flag:
            if(FLAGS&Nz)
                 jmpf_(flag,JMP_flag,addr);
            break;
    }
}
/**
  the CMP instruction is used to compare one specified value to another. the following flags
  describe their use the opp-code instruction is 0b01001, this is preceded by 3 flag bits
  as specified below
    CMP -- 0x01001xxx compares data from a specified flag type to another specified
                      the flag system uses the following opp-code specifications
           0x010011xx compares data from a source to an item in a destination memory address.
           0b010010xx compares data from a source to an item in a destination register
           0b01001x01 compares data from a register to a specified source;
           0b01001x10 compares data from a memory address to the specified source.
           0b01001x11 compares data from a constant type to a specified source.

           their is no way to compare data from a constant type to a constant type

    the CMP instruction does one of the following depending on the result

         if the first parameter is less then the second then the less then flag is set
         in the flags register
         FLAGS -- 0b******** ******** ******** *****001

         if the first parameter is equal to the second parameter then the equality flag
         is set.
         FLAGS -- 0b******** ******** ******** *****010
         if the first parameter is greater then the second parameter then the greater then flag
         is set.
         FLAGS -- 0b******** ******** ******** *****100

        the comparison flag ca be used in conditional jmp instructions

*/
void cmp_(int flag,int Load_a, int Load_b){
    FLAGS &= ClsEqF;
    subMacroDef(cmp,flag,Load_a,Load_b);
}
