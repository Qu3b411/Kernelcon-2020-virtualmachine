#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define Lt          0b00000000000000000000000000000001
#define Eq          0b00000000000000000000000000000010
#define Gt          0b00000000000000000000000000000100
#define Lz          0b00000000000000000000000000000011
#define Gz          0b00000000000000000000000000000110
#define Nz          0b00000000000000000000000000000101
#define ClsEqF      0b11111111111111111111111111111000
/**
   permission context for flags
   firmware permissions
   bios permissions
   kernal permissions
   admin permissions
   user permissions
   guest permissions
*/
#define Firmware            0b10000000000000000000000000000000
#define Bios                0b01000000000000000000000000000000
#define kernal              0b00100000000000000000000000000000
#define admin               0b00010000000000000000000000000000
#define user                0b00001000000000000000000000000000
#define guest               0b00000100000000000000000000000000
#define BootingPermission   0b11111100000000000000000000000000

#define andOpperator(_val1,_val2) _val1 &= _val2;
#define orOpperator(_val1,_val2) _val1 |= _val2;
#define XorOpperator(_val1,_val2) _val1 ^= _val2;
#define addOpperator(_val1,_val2) _val1 += _val2;
#define subOpperator(_val1,_val2) _val1 -= _val2;
#define multOpperator(_val1,_val2) _val1 *= _val2;
#define divOpperator(_val1,_val2) _val1 /= _val2;
#define modOpperator(_val1,_val2) _val1 %= _val2;
#define notOpperator(_val1,_val2) _val1 = ~_val1;
#define movOpperator(_val1,_val2) _val1 = _val2;
#define pushOpperator(_NaN,_val2) *SP=_val2;

#define cmpOpperator(_VAL_,_VAL2_)\
    if (_VAL_>_VAL2_)\
        FLAGS ^=Lt; \
    else if (_VAL_<_VAL2_)\
        FLAGS ^=Gt;\
    else \
        FLAGS^=Eq;

#define paramMacro(_opp,_VAL_,_VAL2_)\
        switch (flag & FLAG_L)\
        {\
            case FLAG_REG:\
                switch (_VAL2_)\
                {\
                    case AX_: _opp##Opperator(_VAL_,AX);break;\
                    case BX_: _opp##Opperator(_VAL_,BX);break;\
                    case CX_: _opp##Opperator(_VAL_,CX);break;\
                    case DX_: _opp##Opperator(_VAL_,DX);break;\
                     default:\
                         if(FLAGS&kernal)\
                            {\
                                switch (_VAL2_)\
                                {\
                                    case DI_:_opp##Opperator(_VAL_,DX);break;\
                                    case IP_:_opp##Opperator(_VAL_,(int)(IP-RAM_base));break;\
                                    case SI_:_opp##Opperator(_VAL_,(int)(SI-RAM_base));break;\
                                    case CS_:_opp##Opperator(_VAL_,(int)(CS-RAM_base));break;\
                                    case SP_:_opp##Opperator(_VAL_,(int)(SP-RAM_base));break;\
                                    case DS_:_opp##Opperator(_VAL_,(int)(DS-RAM_base));break;\
                                    case ES_:_opp##Opperator(_VAL_,(int)(ES-RAM_base));break;\
                               }\
                            }\
                            else\
                            {\
                                puts("error: bad register index");\
                                exit(EXIT_FAILURE);\
                            }\
                }\
            break;\
            case FLAG_ADDR:\
                _opp##Opperator(_VAL_,*(RAM_base+_VAL2_))\
                break;\
            case FLAG_CONST:\
                _opp##Opperator(_VAL_,_VAL2_)\
                break;\
            default:\
                puts("error: invalid syntax flag not valid");\
                exit(EXIT_FAILURE);\
        }

#define subMacroDef(opp,flag,__var1,__var2)\
    if (flag&FLAG_H)\
    {\
        paramMacro(opp,*(RAM_base+__var1),__var2); \
    }\
    else\
    {\
        switch (__var1)\
        {\
            case AX_:paramMacro(opp,AX,__var2);break;\
            case BX_:paramMacro(opp,BX,__var2);break;\
            case CX_:paramMacro(opp,CX,__var2);break;\
            case DX_:paramMacro(opp,DX,__var2);break;\
            default:\
                        badRegError;\
        }\
    }
#define badRegError \
                puts("error: bad register index");\
                free(RAM_base);\
                exit(EXIT_FAILURE)
#define movMacro1(_VAL_,_VAL2_)\
        switch (flag & FLAG_L)\
        {\
            case FLAG_REG:\
                switch (_VAL2_)\
                {\
                    case AX_: _VAL_ = AX;break;\
                    case BX_: _VAL_ = BX;break;\
                    case CX_: _VAL_ = CX;break;\
                    case DX_: _VAL_ = DX;break;\
                    case DI_: _VAL_ = DI;break;\
                     default:\
                        puts("error: bad register index");\
                        exit(EXIT_FAILURE);\
                }\
            break;\
            case FLAG_ADDR:\
                _VAL_ = *(RAM_base+_VAL2_);\
                break;\
            case FLAG_CONST:\
                _VAL_ = _VAL2_;\
                break;\
            default:\
                puts("error: invalid syntax flag not valid");\
                exit(EXIT_FAILURE);\
        }
#define movMacro2(_VAL_,_VAL2_)\
        switch (flag & FLAG_L)\
        {\
            case FLAG_REG:\
                switch (_VAL2_)\
                {\
                    case AX_: _VAL_ = (RAM_base+AX);break;\
                    case BX_: _VAL_ = (RAM_base+BX);break;\
                    case CX_: _VAL_ = (RAM_base+CX);break;\
                    case DX_: _VAL_ = (RAM_base+DX);break;\
                    case SI_: _VAL_ = SI;break;\
                    case SS_: _VAL_ = SS;break;\
                    case IP_: _VAL_ = IP;break;\
                     default:\
                        puts("error: bad register index");\
                        exit(EXIT_FAILURE);\
                }\
            break;\
            case FLAG_ADDR:\
                _VAL_= (RAM_base+(_VAL2_));\
                break;\
            case FLAG_CONST:\
                _VAL_ = (RAM_base+_VAL2_);\
                break;\
            default:\
                puts("error: invalid syntax flag not valid");\
                exit(EXIT_FAILURE);\
        }
#define VmemSIZE    0x1000000
FILE* DISK;
/**
    gloabaly accessed as members of the cpu buss
    DONOT make static, the cpu bus should act in this
    manner.
**/
void KBBuffer();
void readHardDisk();
void videoOut();

int *RAM_base, AX,BX,CX,DX,
* SP, *BP, *SI,DI, *DS, *CS, *SS, *ES, *IP;

/*
    DATA INPUT ON SERIAL BUS 1. CODE REGISTER API.
*/
#define Hardware_SerialInput 0b01

int  USB_BUS_IO_1;
int  SERIAL_BUS_1_HDD_IO_1;
int  BIOS_VIDEO_OUT_BUS_1;
unsigned int FLAGS;
#define INT_TERMINATE 0;
typedef void (*FUNCT_PROTO)();
void HardwareSetup();

void LoadInstructions();
void BOOT();
void INT_(int flagNull, int interuptContext, int setNull);
void mov_(int flag, int Load_a, int Load_b);
void add_(int flag, int a, int b);
void sub_(int flag, int a, int b);
void div_(int flag, int a, int b);
void mult_(int flag, int a, int b);
void push_(int flags, int Load, int setNull);
void pop_(int flag, int reg, int null);
void cmp_(int flag,int Load_a, int Load_b);
void jmp_(int flag, int addr,int setnull);
void jmpf_(int flag, int addr, int setnull);
void nop_(int flag, int a, int b);
void iqrl_(int flag, int a, int setnull);
void and_(int flag,int a, int b);
void or_(int flag,int a, int b);
void xor_(int flag,int a, int b);
void not_(int flag,int a, int setNull);
void mod_(int flag,int a, int b);
#define AX_ 0b0001
#define BX_ 0b0010
#define CX_ 0b0011
#define DX_ 0b0100
#define DI_ 0b0101
#define SI_ 0b0110
#define DS_ 0b0111
#define CS_ 0b1000
#define SS_ 0b1001
#define ES_ 0b1010
#define IP_ 0b1011
#define SP_ 0b1100
#define ORG 0x7c00
#define COMMND_OPP  0b11111000000000000000000000000000
#define FLAG_OPP    0b00000111000000000000000000000000
#define VAR1_FLAG   0b00000000111111111111111111111111
#define VAR2_FLAG   ob11111111111111111111111111111111
#define FLAG_H 0b100
#define FLAG_L 0b011
#define FLAG_REG 0b01
#define FLAG_ADDR 0b10
#define FLAG_CONST 0b11
#define JMP_flag    0b001
#define JL_flag     0b010
#define JE_flag     0b011
#define JG_flag     0b100
#define JLE_flag    0b101
#define JGE_flag    0b110
#define JNE_flag    0b111
#endif // VM_H_INCLUDED
