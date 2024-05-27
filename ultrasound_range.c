#include <stdio.h>
#include "pico/stdlib.h"
#include "ultrasound.h"

#define PIO pio0
#define RX_GPIO 14
#define TX_GPIO 15

int main() {
    stdio_init_all();

    // state machines assigned
    uint rx_sm;
    uint tx_sm;

    // start receiver
    if (rx_init(PIO, &rx_sm, RX_GPIO)) {
        puts("RX running");
    }

    // start transmitter
    if (tx_init (PIO, &tx_sm, TX_GPIO)) {
        puts ("TX running");
    }

    // display periodic samples
    uint sample_num = 0;
    uint phase;
    while(true) {
        phase = pio_sm_get_blocking(PIO, rx_sm);
        sample_num += 1;
        if (sample_num % 1024 == 0) {
            printf("%u\n", phase / 16);
        }
    }
}