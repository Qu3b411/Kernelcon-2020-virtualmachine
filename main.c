
#include "VM.h"
/**
    to program the boot sequence generate a file OS.VKDSK.
    your interrupt vector table exists at 0x000->0x3ff;
    though the interrupts may be programed at this point
    it is best to use jmp instructions and define your functions
    at that point.

    if you use your calling syntax is set up properly then you can
        run a return after the function is called.

    interrupts can be used to implement hardware access to
    usb, hdd, or video out
    to access usb, the virtual hardware address can be found at 0x100:
    to access hdd, the virtual hardware address can be found at 0x101:
    to access video out the virtual hardware address can be found at 0x102:


*/
typedef void(*callback)();
int main()
{   HardwareSetup();
    LoadInstructions();
    BOOT();
    mov_(0b010,AX_,0x100);
    ((callback)((void(*)(void*))*(RAM_base+0x100)))();
    ((callback)((void(*)(void*))*(RAM_base+0x101)))();
    ((callback)((void(*)(void*))*(RAM_base+0x102)))();

    push_(0b001,IP_,0b0000);
    pop_(0b00,AX_,0b0000);
    iqrl_(0b11,BX_,0x00);
    mov_(0b011,0b001,0x00000000);
    add_(0b011,0b001,0xcafebabe);
    free(RAM_base);
    free(DISK);
    return 0;
}
