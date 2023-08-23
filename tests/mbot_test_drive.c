/**
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <pico/stdlib.h>
#include "hardware/pio.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include <mbot/motor/motor.h>
#include <mbot/defs/mbot_params.h>

float right_motor_polarity = 1.0;
float left_motor_polarity = 1.0;
int left_motor = 0;
int right_motor = 2;


void blink();
void example_drive_motor();

int mbot_init_pico(void){    
    // set master clock to 250MHz (if unstable set SYS_CLOCK to 125Mhz)
     if(!set_sys_clock_khz(SYS_CLOCK, true)){
         printf("ERROR mbot_init_pico: cannot set system clock\n");
         return MBOT_ERROR;
     }; 
    
    stdio_init_all(); // enable USB serial terminal
    sleep_ms(500);
    printf("\nMBot Booting Up!\n");
    return MBOT_OK;
}

int main() {
    sleep_ms(500);
    mbot_init_pico();
    sleep_ms(2000);
    printf("\033[2J\r");
    printf("***MBot Motor Test***\n");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    int freq = 5000;
    
    mbot_motor_init_freq(left_motor, 10000);
    mbot_motor_init_freq(right_motor, 10000);
    
    example_drive_motor();
    
    mbot_motor_cleanup(0);
    mbot_motor_cleanup(1);
    mbot_motor_cleanup(2);
    
    blink();
    return 0;
}

void example_drive_motor(){

    /*************************************************************
        * TODO:
        *  - Week 2: Section 1.9
        *      - Modify this section to change the motor speeds, 
        *           directions, and run-times to your liking.
        *
    ************************************************************/

    blink();

    mbot_motor_set_duty(left_motor, left_motor_polarity * 1.0);
    mbot_motor_set_duty(right_motor, right_motor_polarity * 1.0);
    sleep_ms(2000);
    mbot_motor_set_duty(left_motor, left_motor_polarity * 0);
    mbot_motor_set_duty(right_motor, right_motor_polarity * 0);
    sleep_ms(1000);
    mbot_motor_set_duty(left_motor, left_motor_polarity * -0.5);
    mbot_motor_set_duty(right_motor, right_motor_polarity * -0.5);
    sleep_ms(2000);
    mbot_motor_set_duty(left_motor, left_motor_polarity * -0);
    mbot_motor_set_duty(right_motor, right_motor_polarity * -0);
    sleep_ms(500);

    blink();
    printf("Done!\n");
}

void blink() {
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(500);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
}
