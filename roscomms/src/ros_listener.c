#include <roscomms/ros_listener.h>
#include <roscomms/callbacks.h>
#include <roscomms/pico_uart_transport.h>
#include "pico/stdlib.h"

static uint64_t ros_update_time = 0;

rcl_ret_t roscomms_init(){
    rmw_uros_set_custom_transport(
        true,
        NULL,
        pico_serial_transport_open,
        pico_serial_transport_close,
        pico_serial_transport_write,
        pico_serial_transport_read
    );


    allocator = rcl_get_default_allocator();

    rcl_ret_t ret = rmw_uros_ping_agent(1000, 120);

    if (ret != RCL_RET_OK)
    {
        printf("Failed to establish ROS communications"); //Unreachable agent, exiting program.
        return ret;
    }

    rclc_support_init(&support, 0, NULL, &allocator);
    
    rmw_uros_sync_session(1000);

    ros_update_time = rmw_uros_epoch_millis();

    return ret;

}


void roscomms_node_init(){
    
    // Overall Node initialization
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

    // Subscription 1
    // rclc_subscription_init_default(
    //     &subscriber1, // This needs to be a new subscriber for each item
    //     &node,
    //     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32), // Message type
    //     "subscriber_1" // Subscription topic name
    // );

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
    
    // Declaring parameters
    rclc_parameter_options_t option_param = {
    .notify_changed_over_dds = false,
    .max_params = 20
    };

    rclc_parameter_server_init_with_option(&param_server, &node, &option_param);


    


    // Initialize the executor
    rclc_executor_init(&executor, &support.context, RCLC_PARAMETER_EXECUTOR_HANDLES_NUMBER + 6, &allocator);
    
    //Initialize parameter server
    rclc_executor_add_parameter_server(&executor, &param_server, on_parameter_changed);
    rclc_add_parameter(&param_server, "FORWARD_KP", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "FORWARD_KI", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "FORWARD_KD", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "TURN_KP", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "TURN_KI", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "TURN_KD", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "LEFT_FORWARD_M", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "LEFT_FORWARD_B", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "LEFT_BACKWARD_M", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "LEFT_BACKWARD_B", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "RIGHT_FORWARD_M", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "RIGHT_FORWARD_B", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "RIGHT_BACKWARD_M", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "RIGHT_BACKWARD_B", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "ENCODER_POLARITY_LEFT", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "ENCODER_POLARITY_RIGHT", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "MOTOR_POLARITY_LEFT", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "MOTOR_POLARITY_RIGHT", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "WHEEL_BASE", RCLC_PARAMETER_DOUBLE);
    rclc_add_parameter(&param_server, "WHEEL_RADIUS", RCLC_PARAMETER_DOUBLE);
    // Initialize all subscriptions onto the executor
    //rclc_executor_add_subscription(&executor, &subscriber1, &msgsub1, &subscription_callback_generic, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_MBOT_VEL_CMD, &vel_cmd, &subscription_callback_mbot_vel_cmd, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_MBOT_MOTOR_VEL_CMD, &ros_mbot_motor_vel_cmd, &subscription_callback_mbot_motor_vel_cmd, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_MBOT_MOTOR_PWM_CMD, &ros_mbot_motor_pwm_cmd, &subscription_callback_mbot_motor_pwm_cmd, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_RESET_ODOMETRY, &ros_mbot_odom, &subscription_callback_generic, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &ROS_RESET_ENCODERS, &ros_mbot_encoder, &subscription_callback_generic, ON_NEW_DATA);




}

void roscomms_listener_loop(){
    // if((ros_update_time - rmw_uros_epoch_millis()) %1000 == 0){
       // rmw_uros_sync_session(1000);
    //     ros_update_time = rmw_uros_epoch_millis();
    // }
    

    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(0));
   
}

