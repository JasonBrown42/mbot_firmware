#include "odometry.h"
#include <math.h>



int mbot_calculate_differential_body_vel(float wheel_left_vel, float wheel_right_vel, mbot_msg__msg__Twist2dt *mbot_vel, mbot_params_t MBot){
    /*************************************************************
        * TODO:
        *  - Week 3: Section (UPDATE)
        *      - 
        *
    ************************************************************/
    
    mbot_vel->vx = 0;
    mbot_vel->vy = 0;
    mbot_vel->wz = 0;
    return 0; // Return 0 to indicate success
}
// int mbot_calculate_differential_body_vel_imu(float wheel_left_vel, float wheel_right_vel, serial_mbot_imu_t imu, serial_twist2D_t *mbot_vel){
//     return 0; // Return 0 to indicate success
// }
// int mbot_calculate_omni_body_vel(float wheel0_vel, float wheel1_vel, float wheel2_vel, serial_twist2D_t *mbot_vel){
//     return 0; // Return 0 to indicate success
// }
// int mbot_calculate_omni_body_vel_imu(float wheel_0_vel, float wheel_1_vel, float wheel_2_vel, serial_mbot_imu_t imu, serial_twist2D_t *mbot_vel){
//     return 0; // Return 0 to indicate success
// }

int mbot_calculate_odometry(mbot_msg__msg__Twist2dt mbot_vel, float dt, mbot_msg__msg__Pose2dt *odometry){
    /*************************************************************
        * TODO:
        *  - Week 3: Section (UPDATE)
        *      - 
        *
    ************************************************************/
    return 0; // Return 0 to indicate success
}
