// #include <mbot_lcm_msgs_serial.h>
#include <mbot/defs/mbot_params.h>
#include <mbot_msg/msg/twist2dt.h>
#include <mbot_msg/msg/pose2dt.h>
#include <mbot/defs/mbot_params.h>

/**
 * @brief Calculate the body velocity of a differential drive robot
 * 
 * @param[in] wheel_left_vel  Velocity of the left wheel in rad/s
 * @param[in] wheel_right_vel Velocity of the right wheel in rad/s
 * @param[out] mbot_vel       Pointer to the structure where the calculated body velocity will be stored
 * @return int                Returns 0 on success
 */
int mbot_calculate_differential_body_vel(float wheel_left_vel, float wheel_right_vel, mbot_msg__msg__Twist2dt *mbot_vel, mbot_params_t MBot);

/**
 * @brief Calculate the body velocity of a differential drive robot using an IMU for angular velocity
 * 
 * @param[in] wheel_left_vel  Velocity of the left wheel in rad/s
 * @param[in] wheel_right_vel Velocity of the right wheel in rad/s
 * @param[in] imu             IMU data
 * @param[out] mbot_vel       Pointer to the structure where the calculated body velocity will be stored
 * @return int                Returns 0 on success
 */
// int mbot_calculate_differential_body_vel_imu(float wheel_left_vel, float wheel_right_vel, serial_mbot_imu_t imu, serial_twist2D_t *mbot_vel);

/**
 * @brief Calculate the body velocity of an omnidirectional (Kiwi) robot
 * 
 * @param[in] wheel_0_vel Velocity of wheel 0 in rad/s
 * @param[in] wheel_1_vel Velocity of wheel 1 in rad/s
 * @param[in] wheel_2_vel Velocity of wheel 2 in rad/s
 * @param[out] mbot_vel   Pointer to the structure where the calculated body velocity will be stored
 * @return int            Returns 0 on success
 */
// int mbot_calculate_omni_body_vel(float wheel_0_vel, float wheel_1_vel, float wheel_2_vel, serial_twist2D_t *mbot_vel);

/**
 * @brief Calculate the body velocity of an omnidirectional (Kiwi) robot using an IMU for angular velocity
 * 
 * @param[in] wheel_0_vel Velocity of wheel 0 in rad/s
 * @param[in] wheel_1_vel Velocity of wheel 1 in rad/s
 * @param[in] wheel_2_vel Velocity of wheel 2 in rad/s
 * @param[in] imu         IMU data
 * @param[out] mbot_vel   Pointer to the structure where the calculated body velocity will be stored
 * @return int            Returns 0 on success
 */
// int mbot_calculate_omni_body_vel_imu(float wheel_0_vel, float wheel_1_vel, float wheel_2_vel, serial_mbot_imu_t imu, serial_twist2D_t *mbot_vel);

/**
 * @brief Calculate the odometry (position and orientation) of the robot based on its body velocity
 * 
 * @param[in] mbot_vel  Current body velocity of the robot
 * @param[in] dt        Time interval over which the velocity is applied
 * @param[out] odometry Pointer to the structure where the calculated odometry will be stored
 * @return int          Returns 0 on success
 */
int mbot_calculate_odometry(mbot_msg__msg__Twist2dt mbot_vel,  float dt, mbot_msg__msg__Pose2dt *odometry);

