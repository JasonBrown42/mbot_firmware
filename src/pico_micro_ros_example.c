/**
 * This file is the main executable for the MBot firmware.
 */

#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <rmw_microros/rmw_microros.h>

#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include "mbot.h"
// #include "odometry.h"
// #include "print_tables.h"
// #include <mbot/defs/mbot_params.h>
#include "pico_uart_transports.h"

#define THETA "\u0398"
#pragma pack(1)

rcl_publisher_t publisher;
rcl_subscription_t subscriber;

std_msgs__msg__Int32 msg;

// Global
static uint64_t timestamp_offset = 0;
static uint64_t global_utime = 0;
static uint64_t global_pico_time = 0;
static bool global_comms_status = COMMS_OK; 
static int drive_mode = 0;
static bool running = false;
static mbot_params_t MBot;
int i = 0;


void timestamp_cb(serial_timestamp_t *msg)
{
    global_pico_time = to_us_since_boot(get_absolute_time());
    timestamp_offset = msg->utime - global_pico_time;
    global_comms_status = COMMS_OK;
}

void reset_encoders_cb(serial_mbot_encoders_t *msg)
{
    //memcpy(&encoders, msg, sizeof(serial_mbot_encoders_t));
    for(int i=0; i<3; i++){
        mbot_encoder_write(i, msg->ticks[i]);
    }
}

void mbot_vel_cmd_cb(serial_twist2D_t *msg)
{
    memcpy(&mbot_vel_cmd, msg, sizeof(serial_twist2D_t));
    drive_mode = MODE_MBOT_VEL;
}

void mbot_motor_vel_cmd_cb(serial_mbot_motor_vel_t *msg)
{
    memcpy(&mbot_motor_vel_cmd, msg, sizeof(serial_mbot_motor_vel_t));
    drive_mode = MODE_MOTOR_VEL;
}

void mbot_motor_pwm_cmd_cb(serial_mbot_motor_pwm_t *msg)
{
    memcpy(&mbot_motor_pwm_cmd, msg, sizeof(serial_mbot_motor_pwm_t));
    drive_mode = MODE_MOTOR_PWM;
}

void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    i++;
    msg.data = i;
    rcl_ret_t ret = rcl_publish(&publisher, &msg, NULL);
    
}

void subscription_callback(const void * msgin)
{  
    const std_msgs__msg__Int32 * msg_ = (const std_msgs__msg__Int32 *)msgin;
    
        //msg.data = msg_->data;
        // Set motors
        mbot_motor_set_duty(0, msg_->data * 0.1);
        mbot_motor_set_duty(1, msg_->data * 0.1);
        mbot_motor_set_duty(2, msg_->data * 0.1);
}


int mbot_init_pico(void){
    bi_decl(bi_program_description("Firmware for the MBot Robot Control Board"));
    
    // set master clock to 250MHz (if unstable set SYS_CLOCK to 125Mhz)
    if(!set_sys_clock_khz(125000, true)){
        printf("ERROR mbot_init_pico: cannot set system clock\n");
        return MBOT_ERROR;
    }; 
    
    stdio_init_all(); // enable USB serial terminal
    sleep_ms(500);
    printf("\nMBot Booting Up!\n");
    return MBOT_OK;
}

int mbot_init_hardware(void){
    sleep_ms(1000);
    // Initialize Motors
    printf("initializinging motors...\n");
    mbot_motor_init(0);
    mbot_motor_init(1);
    mbot_motor_init(2);
    printf("initializinging encoders...\n");
    mbot_encoder_init();

    // Initialize I2C
    printf("setting i2c bus...\n");
    // Initialize I2C port at 400 kHz
    i2c = i2c0;
    i2c_init(i2c, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, GPIO_FUNC_I2C));

    // Initialize LED
    printf("Starting heartbeat LED...\n");
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    return MBOT_OK;
}

void main()
{   
    mbot_init_pico();
    mbot_init_hardware();
    // mbot_init_comms();
    MBot.robot_type = DIFFERENTIAL_DRIVE;
    MBot.wheel_radius = WHEEL_RADIUS;
    MBot.wheel_base = WHEEL_BASE;
    MBot.gear_ratio = GEAR_RATIO;
    MBot.encoder_resolution = ENCODER_RES;
    MBot.motor_polarity[0] = 1;
    MBot.motor_polarity[2] = -1;
    MBot.encoder_polarity[0] = 1;
    MBot.encoder_polarity[2] = -1;

    // printf("Starting MBot Loop...\n");
    // repeating_timer_t loop_timer;
    // add_repeating_timer_ms(MAIN_LOOP_PERIOD * 1000, mbot_loop, NULL, &loop_timer); // 1000x to convert to ms
    // printf("Done Booting Up!\n");
    

    rmw_uros_set_custom_transport(
        true,
        NULL,
        pico_serial_transport_open,
        pico_serial_transport_close,
        pico_serial_transport_write,
        pico_serial_transport_read
    );

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    rcl_timer_t timer;
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;

    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);

    if (ret != RCL_RET_OK)
    {
        // Unreachable agent, exiting program.
        return ret;
    }

    rclc_support_init(&support, 0, NULL, &allocator);

    rclc_node_init_default(&node, "pico_node", "", &support);
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "pico_publisher");

    // rclc_publisher_init_default(
    //     &publisher_second,
    //     &node,
    //     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    //     // "pico_publisher");

    rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_subscriber");
        

    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(0),
        timer_callback);

    rclc_executor_init(&executor, &support.context, 2, &allocator);
    rclc_executor_add_timer(&executor, &timer);
    rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA);

    gpio_put(LED_PIN, 1);

    msg.data = 0;

    
    while(true){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(0)); 
    }
}