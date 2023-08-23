/**
 * This file is the main executable for the MBot firmware.
 */

#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
// #include <std_msgs/msg/int32.h>
#include <std_msgs/msg/u_int32.h>
#include <rmw_microros/rmw_microros.h>

#include <pico/stdlib.h>
#include <hardware/gpio.h>
// #include "mbot.h"
// #include "odometry.h"
// #include "print_tables.h"
#include <mbot/defs/mbot_params.h>
#include "pico_uart_transports.h"

#define THETA "\u0398"
#pragma pack(1)

rcl_publisher_t publisher;
rcl_subscription_t subscriber;

std_msgs__msg__UInt32 time_msg;

// Global
static uint64_t timestamp_offset = 0;
static uint64_t global_utime = 0;
static uint64_t global_pico_time = 0;
static bool global_comms_status = COMMS_OK; 
static int drive_mode = 0;
static bool running = false;
static mbot_params_t MBot;


void timestamp_cb(serial_timestamp_t *msg)
{
    global_pico_time = to_us_since_boot(get_absolute_time());
    timestamp_offset = msg->utime - global_pico_time;
    global_comms_status = COMMS_OK;
}


void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    rcl_ret_t ret = rcl_publish(&publisher, &time_msg, NULL);
    //msg.data++;
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
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt32),
        "pico_time");

    // rclc_publisher_init_default(
    //     &publisher_second,
    //     &node,
    //     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    //     // "pico_publisher");

    

    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(0),
        timer_callback);

    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_timer(&executor, &timer);
    
    gpio_put(LED_PIN, 1);

    
    while(true){
        time_msg.data = get_absolute_time();
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(0)); 
        printf("Please work\n");
    }
}