#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>
#include "pico/stdlib.h"

#include <std_msgs/msg/int32.h>
#include <mbot_msg/msg/twist2dt.h>
#include <mbot_msg/msg/pose2dt.h>
#include <mbot_msg/msg/mbotencoderst.h>
#include <mbot_msg/msg/mbotmotorpwmt.h>
#include <mbot_msg/msg/mbotmotorvelt.h>
#include <mbot_msg/msg/timestampt.h>
#include <mbot_msg/msg/mbotimut.h>
#include <geometry_msgs/msg/twist.h>
extern int drive_mode;

enum drive_modes{
    MODE_MOTOR_PWM = 0,
    MODE_MOTOR_VEL = 1,
    MODE_MBOT_VEL = 2
};

#include "pico/stdlib.h"
#include <roscomms/pico_uart_transport.h>


rcl_publisher_t ROS_MBOT_VEL;
rcl_publisher_t ROS_MBOT_ODOM;
rcl_publisher_t ROS_MBOT_ENCODER;
rcl_publisher_t ROS_MBOT_MOTOR_PWM;
rcl_publisher_t ROS_MBOT_MOTOR_VEL;
rcl_publisher_t ROS_MBOT_IMU;

// rcl_subscription_t subscriber1;
rcl_subscription_t ROS_MBOT_VEL_CMD;
rcl_subscription_t ROS_MBOT_MOTOR_VEL_CMD;
rcl_subscription_t ROS_MBOT_MOTOR_PWM_CMD;
rcl_subscription_t ROS_RESET_ODOMETRY;
rcl_subscription_t ROS_RESET_ENCODERS;

// std_msgs__msg__Int32 msgpub1;
// std_msgs__msg__Int32 msgsub1;

//Publishers
mbot_msg__msg__Twist2dt ros_mbot_vel; 
mbot_msg__msg__Pose2dt ros_mbot_odom;
mbot_msg__msg__Mbotencoderst ros_mbot_encoder;
mbot_msg__msg__Mbotmotorpwmt ros_mbot_motor_pwm;
mbot_msg__msg__Mbotmotorvelt ros_mbot_motor_vel;
mbot_msg__msg__Mbotimut ros_mbot_imu;

//Subscribers
geometry_msgs__msg__Twist vel_cmd;
mbot_msg__msg__Twist2dt ros_mbot_vel_cmd;
mbot_msg__msg__Mbotmotorpwmt ros_mbot_motor_pwm_cmd;
mbot_msg__msg__Mbotmotorvelt ros_mbot_motor_vel_cmd;

void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    // rcl_ret_t ret = rcl_publish(&publisher, &msg, NULL);
    // msg.data++;
}

void subscription_callback(const void * msgin)
{  
    const geometry_msgs__msg__Twist * msg_ = (const geometry_msgs__msg__Twist *)msgin;
    // if(msg_->data > 0){
    //     msg.data = msg_->data;
    // }
    printf("\n %f %f\r", vel_cmd.linear.x, vel_cmd.angular.z);
    printf("\n %f %f\r", msg_->linear.x, msg_->angular.z);
    printf("\n done \r");
    
}

int drive_mode = 0;
void subscription_callback_generic(const void * msgin)
{  
    return;
}

void subscription_callback_mbot_vel_cmd(const void * msgin)
{ 
    drive_mode = MODE_MBOT_VEL;
    const geometry_msgs__msg__Twist * msg_ = (const geometry_msgs__msg__Twist *)msgin;
    ros_mbot_vel_cmd.vx = vel_cmd.linear.x;
    ros_mbot_vel_cmd.vy = vel_cmd.linear.y;
    ros_mbot_vel_cmd.wz = vel_cmd.angular.z;
    printf("%f %f ; %f %f\r", vel_cmd.linear.x, vel_cmd.angular.z, msg_->linear.x, msg_->angular.z);
    // printf("\n %f %f\r", msg_->linear.x, msg_->angular.z);
    // printf("\n done \r");
}

void subscription_callback_mbot_motor_vel_cmd(const void * msgin)
{ 
    drive_mode = MODE_MOTOR_VEL;
}

void subscription_callback_mbot_motor_pwm_cmd(const void * msgin)
{ 
    drive_mode = MODE_MOTOR_PWM;
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
    // Publisher 1
    rclc_publisher_init_best_effort(
        &ROS_MBOT_VEL, // This needs to be a new publisher for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Twist2dt), // Message type
        "mbot_velocity" // Publisher topic name
    );

    rclc_publisher_init_best_effort(
        &ROS_MBOT_ODOM, // This needs to be a new publisher for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Pose2dt), // Message type
        "mbot_odom" // Publisher topic name
    );

    rclc_publisher_init_best_effort(
        &ROS_MBOT_ENCODER, // This needs to be a new publisher for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Mbotencoderst), // Message type
        "mbot_encoder" // Publisher topic name
    );

    rclc_publisher_init_best_effort(
        &ROS_MBOT_MOTOR_PWM, // This needs to be a new publisher for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Mbotmotorpwmt), // Message type
        "mbot_motors_pwm" // Publisher topic name
    );

    rclc_publisher_init_best_effort(
        &ROS_MBOT_MOTOR_VEL, // This needs to be a new publisher for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Mbotmotorvelt), // Message type
        "mbot_motors_vel" // Publisher topic name
    );

    rclc_publisher_init_best_effort(
        &ROS_MBOT_IMU, // This needs to be a new publisher for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Mbotimut), // Message type
        "mbot_imu" // Publisher topic name
    );

    rclc_subscription_init_best_effort(
        &ROS_MBOT_VEL_CMD, // This needs to be a new subscriber for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), // Message type
        "cmd_vel" // Subscription topic name
        //used to be mbot_vel_cmd
    );
    
    rclc_subscription_init_default(
        &ROS_MBOT_MOTOR_VEL_CMD, // This needs to be a new subscriber for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Mbotmotorvelt), // Message type
        "mbot_motor_vel_cmd" // Subscription topic name
    );
    
    rclc_subscription_init_default(
        &ROS_MBOT_MOTOR_PWM_CMD, // This needs to be a new subscriber for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Mbotmotorpwmt), // Message type
        "mbot_motor_pwm_cmd" // Subscription topic name
    );

    rclc_subscription_init_default(
        &ROS_RESET_ODOMETRY, // This needs to be a new subscriber for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Pose2dt), // Message type
        "mbot_odometry_reset" // Subscription topic name
    );

    rclc_subscription_init_default(
        &ROS_RESET_ENCODERS, // This needs to be a new subscriber for each item
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(mbot_msg, msg, Mbotencoderst), // Message type
        "mbot_encoders_reset" // Subscription topic name
    );
    
    



    // Initialize the executor
    rclc_executor_init(&executor, &support.context, 11, &allocator);
        
    // Initialize all subscriptions onto the executor
    //rclc_executor_add_subscription(&executor, &subscriber1, &msgsub1, &subscription_callback_generic, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_MBOT_VEL_CMD, &vel_cmd, &subscription_callback_mbot_vel_cmd, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_MBOT_MOTOR_VEL_CMD, &ros_mbot_motor_vel_cmd, &subscription_callback_mbot_motor_vel_cmd, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_MBOT_MOTOR_PWM_CMD, &ros_mbot_motor_pwm_cmd, &subscription_callback_mbot_motor_pwm_cmd, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_RESET_ODOMETRY, &ros_mbot_odom, &subscription_callback_generic, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_RESET_ENCODERS, &ros_mbot_encoder, &subscription_callback_generic, ON_NEW_DATA);


    printf("created and can seee \n\r");
    while (true)
    {

        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(0));
        sleep_ms(20);
        
    }
    return 0;
}
