/* MCU is STM32F072VBT7 128K flash and 64K SRAM */

MEMORY {
    FLASH : org = 0x08000000, l = 0x20000
    RAM : org = 0x20000000, l = 0x4000
}

SECTIONS {
    .org_fw : {
        . = . ;
    } >FLASH

    .text 0x0801DF90 : {
        *(.text)
    } > FLASH

    .hook_send_frame 0x080086F0 : {
        *(.hook_send_frame)
    } >FLASH



    spi_send = 0x08008FDC;
    memcpy0 = 0x0800426E;
    channel_buffer = 0x200023B8;
}
