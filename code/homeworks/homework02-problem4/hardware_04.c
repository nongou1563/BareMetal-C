#include <stdbool.h>
#include <stdint.h>

#define LED1 ((volatile bool *)0xE001U)
#define LED2 ((volatile bool *)0xE002U)

void main(void) {

    volatile bool *led01; 
    led01 = LED1;
    volatile bool *led02; 
    led02 = LED2;
    

    while (true) {
        *led01 = true;
        *led01 = false;
        
        *led02 = true;
        *led02 = false;

        *led01 = true;
        *led01 = false;

        *led02 = true;
        *led02 = false;

        *led01 = true;
        *led01 = false;

        *led02 = true;
        *led02 = false;
    }

}
