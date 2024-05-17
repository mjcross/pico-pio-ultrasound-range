#include <stdio.h>
#include "hardware/gpio.h"
#include "squarewave.h"

bool squarewave_init (PIO pio, uint *p_sm, uint gpio) {
    // add the program to the PIO shared instruction memory
    if (pio_can_add_program (pio, &squarewave_program) == false) {
        puts ("could not add the pio program");
        return false;
    }
    uint offset = pio_add_program (pio, &squarewave_program);

    // claim a free state machine
    int sm = pio_claim_unused_sm (pio, false);
    if (sm == -1) {
        puts ("could not claim a state machine");
        return false;
    } else {
        *p_sm = (uint)sm;
    }

    // set the gpio pin function to PIO output
    pio_gpio_init (pio, gpio);
    pio_sm_set_consecutive_pindirs (pio, *p_sm, gpio, 1, true);

    // configure and enable the state machine
    squarewave_sm_init (pio, *p_sm, offset, gpio);

    return true;
}