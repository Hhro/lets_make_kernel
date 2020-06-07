#ifndef PIT_HPP_
#define PIT_HPP_
#include<kapi/idt.hpp>
#include<kapi/io.hpp>
#include<fried/stdio.h>


#define PIT_FREQUENCY 1193182

#define PIT_PORT_CHANNEL_N(N) (0x40 | ((N)&0x3))
#define PIT_PORT_CONTROL 0x43

#define PIT_COMMAND_LATCH(CHANNEL) (((CHANNEL)&3)<<5)
#define PIT_COMMAND_COUNTER0 0x00
#define PIT_COMMAND_LSBMSBRW 0x30
#define PIT_COMMAND_MODE0 0x00
#define PIT_COMMAND_MODE2 0x04
#define PIT_COMMAND_BINARYCOUNTER 0x00
#define PIT_COMMAND_BCDCOUNTER 0x01

#define PIT_COUNTER0_REPEAT (PIT_COMMAND_COUNTER0 | PIT_COMMAND_LSBMSBRW | \
                            PIT_COMMAND_MODE2 | PIT_COMMAND_BINARYCOUNTER )
#define PIT_COUNTER0_ONCE (PIT_COMMAND_COUNTER0 | PIT_COMMAND_LSBMSBRW | \
                            PIT_COMMAND_MODE0 | PIT_COMMAND_BINARYCOUNTER )


class PITDevice {
private:
    int32_t frequency_0, frequency_1, frequency_2, IRQ0_frequency, IRQ0_ms, IRQ0_fraction;
    uint16_t IRQ0_reload;
    uint64_t system_timer_ms, system_timer_fraction;
public:
    PITDevice(int32_t fre_0, int32_t fre_1=-1, int32_t fre_2=-1) \
    :frequency_0(fre_0),frequency_1(fre_1),frequency_2(fre_2),\
    IRQ0_fraction(0), IRQ0_frequency(0), IRQ0_ms(0), IRQ0_reload(0) {
        printf_("Abcd");
    }

    bool set_PIT_counter(uint8_t channel, uint16_t count);
    bool read_PIT_counter(uint8_t channe, uint16_t * count_val);
    void init_IRQ0(int32_t frequency);
    void add_tick();
    void show_tick();
};

#endif