#include <stdio.h>
#include "hardware/gpio.h"
#include "ultrasound.h"
#include "rx.pio.h"     // generated by PIOASM

bool rx_init (PIO pio, uint *p_sm, uint gpio) {
    // add the program to the PIO shared instruction memory
    if (pio_can_add_program (pio, &rx_program) == false) {
        puts ("could not add the RX program");
        return false;
    }
    uint offset = pio_add_program (pio, &rx_program);

    // claim a free state machine
    int sm = pio_claim_unused_sm (pio, false);
    if (sm == -1) {
        puts ("could not claim a state machine for RX");
        return false;
    } else {
        *p_sm = (uint)sm;
    }

    // initialise the GPIO pin for the receiver (defaults to input)
    gpio_init(gpio);        // reset GPIO and set as input
    gpio_disable_pulls(gpio);

    // configure and enable the state machine
    rx_sm_init (pio, *p_sm, offset, gpio);

    return true;
}