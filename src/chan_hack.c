
void spi_send(char *buf, int count);
void memcpy0(char *dst, char *src, int count);

extern char channel_buffer[];

/*
    The firmware sends the radio frames with code that is being executed
    by the interrupt handler of a timer.
    The timer code itself is not responsible for the putting together of the
    radio frame - this is done from the main loop - it simply sends whatever
    is in the radio frame buffer.
    
    The device's analog inputs are read constantly with the ADC which uses DMA.
    The channels' raw ADC data is converted (scaled, mixed, etc.) to the
    actual channel values (1000-2000) on every iteration of the main loop.
    
    The main loop also builds the radio frame that should be sent by the timer code.
    For some reason (I didn't find the exact reason since the state machine which
    controls this is quite complex) this radio frame is built less frequently than
    it is actually being sent. That's why the timer code sends several frames with the same
    content.
    
    Instead of trying to understand the complex state machine and trying to figure out
    where its logic fails, a simpler approach is taken:
    
    The code below is injected just before a radio frame is sent over SPI to the A7105
    chip. It recognizes if the frame carries channel data and if it does, it simply
    copies the channels from the channel buffer which is propely updated on every
    iteration of the main loop.
*/

int chan_hack (char *buf, int count) {
    // AFHDS 2
    if(count == 39 && buf[1] == 0x58) {
        // copy 10 channels
        memcpy0(buf+10, channel_buffer, 2*10);
    }
    // AFHDS
    else if(count == 22 && buf[1] == 0x55) {
        // copy 8 channels
        memcpy0(buf+6, channel_buffer, 2*8);
    }
    
    spi_send(buf, count);
}
