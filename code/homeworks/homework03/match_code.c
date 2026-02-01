#include <stdbool.h>
#include <stdint.h>

#define LED_ADDR      ((uint8_t *)0xE000)
#define SWITCH_START  ((uint8_t *)0xC010)

void main(void) {
    uint8_t target_code[8] = {1, 0, 0, 0, 0, 0, 0, 1};

    while (true) {
        bool is_match = true;

        for (int i = 0; i < 8; i++) {
            if (*(SWITCH_START + i) != target_code[i]) {
                is_match = false;
                break;
            }
        }

        if (is_match) {
            *LED_ADDR = 1;
        } else {
            *LED_ADDR = 0;
        }
    }
}
