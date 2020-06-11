#include<pit.hpp>

bool PITDevice::set_PIT_counter(uint8_t channel, uint16_t count){
    switch(channel){
        case 0:
            if(frequency_0 == -1) return false;
            break;
        case 1:
            if(frequency_1 == -1) return false;
            break;
        case 2:
            if(frequency_2 == -1) return false;
            break;
        default:
            return false;
    }
    
    disableInterrupt();
    outb(PIT_PORT_CHANNEL_N(channel), (count&0xff));
    outb(PIT_PORT_CHANNEL_N(channel), count>>8);
    enableInterrupt();

    return true;
}

bool PITDevice::read_PIT_counter(uint8_t channel, uint16_t *counter_val){
    switch(channel){
        case 0:
            if(frequency_0 == -1) return false;
            break;
        case 1:
            if(frequency_1 == -1) return false;
            break;
        case 2:
            if(frequency_2 == -1) return false;
            break;
        default:
            return false;
    }

    uint8_t l_byte, h_byte;
    disableInterrupt();

    outb(PIT_PORT_CONTROL, PIT_COMMAND_LATCH(channel));

    l_byte = inb(PIT_PORT_CHANNEL_N(channel));
    h_byte = inb(PIT_PORT_CHANNEL_N(channel));
    *counter_val = (h_byte<<8) | l_byte;
    enableInterrupt();

    return true;
}

void PITDevice::init_IRQ0(int32_t frequency){
    uint32_t saved_reload_val, real_fre, quota;
    uint64_t tmp;
    frequency_0 = frequency;

    if(frequency_0 < 18) saved_reload_val = 0x10000;
    else if(frequency_0 > 1193181) saved_reload_val = 1;
    else{
        quota = 3579545LL / frequency_0;
        if(3579545LL % frequency_0 > 3579545LL/2) quota++;
        saved_reload_val = quota/3;
        if(quota%3 > 3/2) saved_reload_val++;
    }

    quota = 3579545LL / saved_reload_val;
    if(3579545LL % saved_reload_val > 3579545LL/2) quota++;
    real_fre = quota/3;
    if(quota%3 > 3/2) real_fre++;
    
    tmp = saved_reload_val * 0xDBB3A062LL;

    IRQ0_ms = (((uint64_t)(tmp & 0xfffffc0000000000LL))>>32);
    IRQ0_fraction = ((uint64_t)(tmp&0x3fffffffc00LL))>>10;
    IRQ0_reload = saved_reload_val;
    IRQ0_frequency = real_fre;

    outb(PIT_PORT_CONTROL, PIT_COUNTER0_REPEAT);
    set_PIT_counter(0, IRQ0_reload);
}

void PITDevice::add_tick(){
    system_timer_fraction += IRQ0_fraction;
    system_timer_ms += IRQ0_ms;
    if(system_timer_fraction > 0xffffffff) {
        system_timer_ms++;
        system_timer_fraction &= 0xffffffff;
    }
    return;
}

void PITDevice::show_tick(){
    printf("ms : %lld, fraction : %llu\n", system_timer_ms, system_timer_fraction);
    return;
}

PITDevice DPIT(8000);
