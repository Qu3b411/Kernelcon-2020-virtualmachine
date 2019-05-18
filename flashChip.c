#include "VM.h"
char _detectEndian(){
    short word = 0x0011;
    char* temp=  (char*) &(word);
    return temp[0];
}
void HardwareSetup()
{
    /*
        set the FLAGS to the default booting permissions
        specified.
    */
    FLAGS = BootingPermission;
    /*
        allocate the space for the 32 bit stack.
    */
    RAM_base= malloc(sizeof(int)*VmemSIZE);
    /*
        south bus initiation.
            1parse io controllers for sector 0x000:0x8000 -> 0x80ff
            read ROM.fchp to 0x000:0xC000 ->0xffff;
    */
    USB_BUS_IO_1 = (int)&KBBuffer;
    SERIAL_BUS_1_HDD_IO_1 = (int)&readHardDisk;
    BIOS_VIDEO_OUT_BUS_1 = (int)&videoOut;


}
typedef int (*callback)();
/**
    load instructions acts as an artificial flash chip to avoid
    unneccessary complexities for early development.
    future modifications may include the use of assembly chip programming.
    boot will start the software at 0x7c00 hardware will have direct
    access to modify the ram, thus eliminating the north and south gates

    after loading the instructions the bytes between 0x400 and 0x 0x4ff
    will be over written for BIOS information, in file this area of memory
    should be skipped.
    the USB bus 1 is loaded at address 0x100, this module will act like the
    keyboard and only take ascii input
    the serial bus to the hard disk drive is loaded at offset 0x101
    the bios output is loaded at offset 0x102;
    flags
**/
void LoadInstructions(){
    DISK = fopen("OS.VKDSK", "r+");
    /*0x7c00 +0x200 = 0x7e00, 0x100000*/
    fgets((char*)RAM_base,0x8000,DISK);
    int x = 0;
    int temp = 0 ;

    if(_detectEndian())
    {
        for (; x <0x8000; x++)
        {
            temp = *(RAM_base+x);
            char* fixEndian=(char*) &(temp);
            int y = 0;
            *(RAM_base+x)=0;
            for(;y<sizeof(int);y++)
            {
                *(RAM_base+x)<<=8;
                *(RAM_base+x)|=*(fixEndian+y);
            }
        }
        /*
            next load serial address ports to memory manually,
        */
    }
    /*
        set up hardware ports at memory addresses 0x000:0x400 -> 0x000:0x408
    */
        mov_(0b111,0x100,USB_BUS_IO_1); /* set the usb bus to memory address 0x400*/
        mov_(0b111,0x101,SERIAL_BUS_1_HDD_IO_1); /* set the hard disk bus to memory address 0x404*/
        mov_(0b111,0x102,BIOS_VIDEO_OUT_BUS_1);/*set the bios video output bus to memory address 0x408*/
        /*
            0x000:0x40c ->0x000:0x4f7 keyboqard buffer;
            0x000:0x4f8->0x4fb keyboard buffer base point
            0x000;0x4fc->0x4ff kekyboard top pointer
        */


}
/**
    from 0000:0000 -> 0000:0300 interrupt table. use offsets to call this
    jump table.

**/
static FUNCT_PROTO FUNCT[] = {
    *nop_,*add_,*sub_,*div_,*mult_,*push_,*pop_,*mov_,*INT_,
    *cmp_,*jmp_,*jmpf_,*iqrl_,*and_,*or_,*xor_,*not_,*mod_};

void BOOT()
{
    IP=RAM_base+(0x7c00/4); /* org 0x7c00/4 due to pointer behavior*/
    for (;IP!=RAM_base+(0x7c80/4);IP+=2)
        FUNCT[(*(IP)&COMMND_OPP)>>27]((*(IP)&FLAG_OPP)>>24,*(IP)&VAR1_FLAG,*(IP+1));
}
