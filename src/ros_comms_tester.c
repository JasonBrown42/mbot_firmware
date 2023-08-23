#include <pico/stdlib.h>
#include <hardware/gpio.h>
// #include "mbot.h"
// #include "odometry.h"
// #include "print_tables.h"
#include <mbot/defs/mbot_params.h>
#include "mbot.h"
#include <roscomms/ros_listener.h>

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

int test_init_comms(void){
    printf("Initializing LCM serial communication...\r\n");
    roscomms_init();
    roscomms_node_init();
    // launch the other core's comm loop
    //printf("starting comms on core 1...\r\n");
    //multicore_launch_core1(roscomms_listener_loop);
   // roscomms_listener_loop();
    // wait for other core to get rolling
    sleep_ms(500);
    return MBOT_OK;
}



void main(){
    mbot_init_pico();
    test_init_comms();
    // ROS_MBOT_VEL.vx=0;
    while(true){
        ros_mbot_vel.utime = to_us_since_boot(get_absolute_time());
        // printf("We're coming to you live from Core 0 (probably): %d \r\n", msgsub1.data);
        rcl_ret_t rc = rcl_publish(&ROS_MBOT_VEL, &ros_mbot_vel, NULL);
        if(rc != RCL_RET_OK){
            printf("The print didn't return okay \r\n");
        }
        // msgpub1.data++;
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(0));
    }
}