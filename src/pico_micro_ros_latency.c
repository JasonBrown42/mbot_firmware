#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "pico_uart_transports.h"


const uint LED_PIN = 25;

uint32_t previouspicotime;

rcl_publisher_t publisher;

rcl_publisher_t publisher_second;

rcl_subscription_t subscriber;

std_msgs__msg__Int32 msg;


int i = 0;


void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    msg.data = get_absolute_time();
    // if(msg.data == 1)
    // {
    //     previouspicotime = get_absolute_time();
    // }
    rcl_ret_t ret = rcl_publish(&publisher, &msg, NULL);
    // i++;
}

void subscription_callback(const void * msgin)
{  
    float avgnum = 5000;
    const std_msgs__msg__Int32 * msg_ = (const std_msgs__msg__Int32 *)msgin;
    // if(msg_->data == avgnum){
    //     printf("The time difference was: %lf\r", (float) ((get_absolute_time() - previouspicotime)/1000.0)/avgnum) ;
    // }
    
}

int main()
{
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
    

    while (true)
    {
        // rcl_publish(&publisher, &msg, NULL);
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(0));
        // printf("Synced time: %lf, Pico time: %lf\r", (double) rmw_uros_epoch_nanos(), (double)get_absolute_time());
        
    }
    return 0;
}
