#ifndef MBOT_H
#define MBOT_H

#include <pico/stdlib.h>
#include <pico/mutex.h>
#include <pico/multicore.h>
#include <pico/time.h>
#include <hardware/gpio.h>
#include <mbot/motor/motor.h>
#include <mbot/encoder/encoder.h>
#include <mbot/motor/motor.h>
#include <mbot/defs/mbot_pins.h>
#include <mbot/defs/mbot_params.h>
#include <mbot/fram/fram.h>
#include <rc/math/filter.h>
#include <rc/mpu/mpu.h>
#include <comms/common.h>
#include <comms/protocol.h>
#include <comms/listener.h>
#include <comms/topic_data.h>
#include <comms/mbot_channels.h>
// #include <mbot_lcm_msgs_serial.h>
#include <roscomms/ros_listener.h>

#include <math.h>
#include <inttypes.h>

#define MESSAGE_CONFIRMATION_CHANNEL "MSG_CONFIRM"

// TODO: Decide which controller is used, open loop = 1, PID = 0
#define OPEN_LOOP 1





// These are for the older MPU9250
// Will be replaced with BHI160
static rc_mpu_data_t mpu_data;
static rc_mpu_config_t mpu_config;

// Global pointer to the i2c bus
static i2c_inst_t *i2c;

// data to hold calibration coefficients
float coeffs[12];  // 4 calibration parameters per motor 

// enum drive_modes{
    // MODE_MOTOR_PWM = 0,
//     MODE_MOTOR_VEL = 1,
//     MODE_MBOT_VEL = 2
// };

/*
* Messages used by the MBot code, 
* we also use these to store state
*/
// origin: mbot
//serial_mbot_imu_t mbot_imu = {0};
//serial_pose2D_t mbot_odometry = {0};
//serial_mbot_encoders_t mbot_encoders = {0};
// serial_twist2D_t mbot_vel = {0};
// serial_mbot_motor_pwm_t mbot_motor_pwm = {0};
//serial_mbot_motor_vel_t mbot_motor_vel = {0};

// origin: comms
//serial_twist2D_t mbot_vel_cmd = {0};
// serial_mbot_motor_pwm_t mbot_motor_pwm_cmd = {0};
// serial_mbot_motor_vel_t mbot_motor_vel_cmd = {0};
//serial_timestamp_t mbot_received_time = {0};

//callback functions
//void timestamp_cb(void);
// void reset_encoders_cb(serial_mbot_encoders_t *msg);
// void reset_odometry_cb(serial_pose2D_t *msg);
// void mbot_vel_cmd_cb(serial_twist2D_t *msg);
// void mbot_motor_vel_cmd_cb(serial_mbot_motor_vel_t *msg);
// void mbot_motor_pwm_cmd_cb(serial_mbot_motor_pwm_t *msg);
bool mbot_loop(repeating_timer_t *rt);
void mbot_read_encoders(mbot_msg__msg__Mbotencoderst* encoders);
void mbot_calculate_motor_vel(mbot_msg__msg__Mbotencoderst encoders, mbot_msg__msg__Mbotmotorvelt *motor_vel);

void mbot_read_encoders(mbot_msg__msg__Mbotencoderst* encoders);
void mbot_calculate_motor_vel(mbot_msg__msg__Mbotencoderst encoders, mbot_msg__msg__Mbotmotorvelt *motor_vel);


#endif
