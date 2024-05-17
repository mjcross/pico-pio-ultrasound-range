#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "ultrasound.h"

#define TX_GPIO 15
#define TX_FREQ_HZ 41000

int main() {
    stdio_init_all();

    uint tx_sm;
    uint tx_clk_div = clock_get_hz(clk_sys) / (2 * TX_FREQ_HZ);
    if (tx_init (pio0, &tx_sm, TX_GPIO, tx_clk_div)) {
        puts ("TX running");
    }

    puts ("done");
    while (true);
}