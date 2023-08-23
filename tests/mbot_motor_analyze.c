#include <stdio.h>
#include <stdint.h>
#include <mbot/motor/motor.h>
#include <mbot/encoder/encoder.h>
#include <mbot/defs/mbot_params.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>

#define INT_16_MAX 32768
#define TIMESTEP_S 1.5
#define NUM_POINTS 25

#define LEFT_ENC_POL 1.0
#define RIGHT_ENC_POL 1.0
#define LEFT_MOTOR_POL 1.0
#define RIGHT_MOTOR_POL 1.0
#define PI 3.1415926535897932384626833279

void blink();

int main() {
    const float I_conversion_factor = 2 * 3.3f / (1 << 12);
    const float RPM_conversion_factor = 60.0 / (GEAR_RATIO * TIMESTEP_S * ENCODER_RES);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
    mbot_motor_init(0);
    mbot_motor_init(1);
    mbot_motor_init(2);
    mbot_encoder_init();
    blink();
    sleep_ms(1000*TIMESTEP_S);
    printf("\nTesting motor 0...\n");
    int32_t d = 0;
    
    int encoder_reading_l, encoder_reading_r;
    float current_reading;
    float wheel_speed_l, wheel_speed_r;
    printf("Left operation Forward\n");
    printf("\nDuty (PWM),Left Speed (m/s),Right Speed (m/s)\n");
    adc_select_input(0);
    for (float duty = 0.0; duty <= 1.05; duty += 0.04) {
        mbot_motor_set_duty(0, LEFT_MOTOR_POL*duty);
        mbot_motor_set_duty(2, 0);
        encoder_reading_l = LEFT_ENC_POL * mbot_encoder_read_delta(0);
        encoder_reading_r = RIGHT_ENC_POL * mbot_encoder_read_delta(2);
        wheel_speed_l = RPM_conversion_factor * encoder_reading_l * WHEEL_DIAMETER * PI / 60; // m/s
        wheel_speed_r = RPM_conversion_factor * encoder_reading_r * WHEEL_DIAMETER * PI / 60; // m/s
        printf("%f,%f,%f\n", (float)duty, wheel_speed_l, wheel_speed_r);
        sleep_ms(1000*TIMESTEP_S);
    }

    printf("Left operation Backward\n");
    printf("\nDuty (PWM),Left Speed (m/s),Right Speed (m/s)\n");
    adc_select_input(0);
    for (float duty = 0.0; duty <= 1.05; duty += 0.04) {
        mbot_motor_set_duty(0, -1.0 * LEFT_MOTOR_POL*duty);
        mbot_motor_set_duty(2, 0);
        encoder_reading_l = LEFT_ENC_POL * mbot_encoder_read_delta(0);
        encoder_reading_r = RIGHT_ENC_POL * mbot_encoder_read_delta(2);
        wheel_speed_l = RPM_conversion_factor * encoder_reading_l * WHEEL_DIAMETER * PI / 60; // m/s
        wheel_speed_r = RPM_conversion_factor * encoder_reading_r * WHEEL_DIAMETER * PI / 60; // m/s
        printf("%f,%f,%f\n", (float) -1.0 * duty, wheel_speed_l, wheel_speed_r);
        sleep_ms(1000*TIMESTEP_S);
    }

    printf("Right operation Forward\n");
    printf("\nDuty (PWM),Left Speed (m/s),Right Speed (m/s)\n");
    for (float duty = 0.0; duty <= 1.05; duty += 0.04) {
        mbot_motor_set_duty(0, 0);
        mbot_motor_set_duty(2, RIGHT_MOTOR_POL*duty);
        encoder_reading_l = LEFT_ENC_POL * mbot_encoder_read_delta(0);
        encoder_reading_r = RIGHT_ENC_POL * mbot_encoder_read_delta(2);
        wheel_speed_l = RPM_conversion_factor * encoder_reading_l * WHEEL_DIAMETER * PI / 60; // m/s
        wheel_speed_r = RPM_conversion_factor * encoder_reading_r * WHEEL_DIAMETER * PI / 60; // m/s
        printf("%f,%f,%f\n", (float)duty, wheel_speed_l, wheel_speed_r);
        sleep_ms(1000*TIMESTEP_S);
    }

    printf("Right operation Backward\n");
    printf("\nDuty (PWM),Left Speed (m/s),Right Speed (m/s)\n");
    for (float duty = 0.0; duty <= 1.05; duty += 0.04) {
        mbot_motor_set_duty(0, 0);
        mbot_motor_set_duty(2, -1 * RIGHT_MOTOR_POL*duty);
        encoder_reading_l = LEFT_ENC_POL * mbot_encoder_read_delta(0);
        encoder_reading_r = RIGHT_ENC_POL * mbot_encoder_read_delta(2);
        wheel_speed_l = RPM_conversion_factor * encoder_reading_l * WHEEL_DIAMETER * PI / 60; // m/s
        wheel_speed_r = RPM_conversion_factor * encoder_reading_r * WHEEL_DIAMETER * PI / 60; // m/s
        printf("%f,%f,%f\n", (float) -1.0 *duty, wheel_speed_l, wheel_speed_r);
        sleep_ms(1000*TIMESTEP_S);
    }

    mbot_motor_set_duty(0, 0);
    mbot_motor_set_duty(2, 0);
    
    blink();
    printf("\nDone!\n");
    mbot_motor_cleanup(0); 
    blink();
    return 0;
}

void blink() {
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    sleep_ms(500);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
}
