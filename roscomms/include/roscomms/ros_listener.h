#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rclc_parameter/rclc_parameter.h>
#include <rmw_microros/rmw_microros.h>
#include "pico/stdlib.h"
#include <roscomms/pico_uart_transport.h>

#include <std_msgs/msg/int32.h>
#include <mbot_msg/msg/twist2dt.h>
#include <mbot_msg/msg/pose2dt.h>
#include <mbot_msg/msg/mbotencoderst.h>
#include <mbot_msg/msg/mbotmotorpwmt.h>
#include <mbot_msg/msg/mbotmotorvelt.h>
#include <mbot_msg/msg/timestampt.h>
#include <mbot_msg/msg/mbotimut.h>
#include <geometry_msgs/msg/twist.h>

#include <mbot/defs/mbot_params.h>


#ifndef ROS_LISTENER_H__
#define ROS_LISTENER_H__
extern int drive_mode;

enum drive_modes{
    MODE_MOTOR_PWM = 0,
    MODE_MOTOR_VEL = 1,
    MODE_MBOT_VEL = 2
};

rcl_timer_t timer;
rcl_node_t node;
rcl_allocator_t allocator;
rclc_support_t support;
rclc_executor_t executor;

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

//Parameter Server
rclc_parameter_server_t param_server;
// extern rclc_parameter_options_t option_param;

rcl_ret_t roscomms_init();
void roscomms_node_init();
void roscomms_listener_loop();

mbot_params_t MBot ; 
// = {DIFFERENTIAL_DRIVE,WHEEL_RADIUS,WHEEL_BASE,GEAR_RATIO,ENCODER_RES,
//     0, 2, 1, {-1,1,-1}, {1,1,1}, {0.7,0.7,0.7}, {0.0,0.0,0.0}, {0.7,0.7,0.7}, {0.0,0.0,0.0},
//     {1.0,0.0,0.0},{1.0,0.0,0.0}};

// MBot.robot_type = DIFFERENTIAL_DRIVE;
// MBot.wheel_radius = WHEEL_RADIUS;
// MBot.wheel_base = WHEEL_BASE;
// MBot.gear_ratio = GEAR_RATIO;
// MBot.encoder_resolution = ENCODER_RES;
// MBot.mot_left = 0;
// MBot.mot_right = 2;
// MBot.mot_back = 1;
// MBot.motor_polarity[3] = [-1,1,-1];
// MBot.encoder_polarity[3] = [1,1,1];
// MBot.slope_pos[3] = [0.7,0.7,0.7];
// MBot.intercept_pos[3] = [0.0,0.0,0.0];
// MBot.slope_neg[3] = [0.7,0.7,0.7];
// MBot.intercept_neg[3] = [0.0,0.0,0.0];
// MBot.forward_gain[3] = [1.0,0.0,0.0];
// MBot.turn_gain[3] = [1.0,0.0,0.0];




#endif 