/**
 * This file is the main executable for the MBot firmware.
 */
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include "mbot.h"
#include "odometry.h"
#include "print_tables.h"



#define THETA "\u0398"
#pragma pack(1)
// Global
static uint64_t timestamp_offset = 0;
static uint64_t global_utime = 0;
static uint64_t global_pico_time = 0;
static bool global_comms_status = COMMS_ERROR; 
// static int drive_mode = 0;
static bool running = false;


//TODO: this should be tied to the IMU interrupt
bool mbot_loop(repeating_timer_t *rt)
{
    global_utime =  rmw_uros_epoch_millis() ;  // 
    //global_utime = to_us_since_boot(get_absolute_time()) + timestamp_offset;
    ros_mbot_vel.utime = global_utime;
    ros_mbot_motor_vel.utime = global_utime;
    ros_mbot_odom.utime = global_utime;
    mbot_read_encoders(&ros_mbot_encoder);
    //mbot_read_imu(&ros_mbot_imu);
    mbot_calculate_motor_vel(ros_mbot_encoder, &ros_mbot_motor_vel);
    mbot_calculate_differential_body_vel(ros_mbot_motor_vel.velocity[0], ros_mbot_motor_vel.velocity[2], &ros_mbot_vel, MBot);
    mbot_calculate_odometry(ros_mbot_vel, MAIN_LOOP_PERIOD, &ros_mbot_odom);



    // only run if we've got 2 way communication...
    if (global_comms_status == COMMS_OK)
    {
        if(drive_mode == 1){
            ros_mbot_motor_pwm.utime = global_utime;

            ros_mbot_motor_pwm.pwm[MBot.mot_left] = MBot.motor_polarity[MBot.mot_left] * (ros_mbot_motor_vel_cmd.velocity[MBot.mot_left] -  MBot.intercept_pos[MBot.mot_left])/MBot.slope_pos[MBot.mot_left];
            ros_mbot_motor_pwm.pwm[MBot.mot_right] = MBot.motor_polarity[MBot.mot_right] * (ros_mbot_motor_vel_cmd.velocity[MBot.mot_right] - MBot.intercept_pos[MBot.mot_right])/MBot.slope_pos[MBot.mot_right];
            ros_mbot_motor_pwm.pwm[MBot.mot_back] = 0;
            // printf("PWM values are: Left: %f, Right: %f",ros_mbot_motor_pwm.pwm[MBot.mot_left], ros_mbot_motor_pwm.pwm[MBot.mot_right]);

            if(ros_mbot_motor_vel_cmd.velocity[0] == 0 && ros_mbot_motor_vel_cmd.velocity[2] == 0){
                ros_mbot_motor_pwm.pwm[0] = 0;
                ros_mbot_motor_pwm.pwm[1] = 0;
                ros_mbot_motor_pwm.pwm[2] = 0;
            }
            
            //mbot_motor_vel_controller(ros_mbot_motor_vel_cmd, ros_mbot_motor_vel, &mbot_motor_pwm);
        }
        else if(drive_mode == 2){    
            // printf("We are receiving velocity commands\r\n");
            ros_mbot_motor_pwm.utime = global_utime;
            
            float INTERCEPT_L = -0.0;
            float INTERCEPT_R = -0.0;

            float SLOPE_L = .7;
            float SLOPE_R = .7;

            float target_l_vel = ros_mbot_vel_cmd.vx - MBot.wheel_base * ros_mbot_vel_cmd.wz / 2;
            float target_r_vel = ros_mbot_vel_cmd.vx + MBot.wheel_base * ros_mbot_vel_cmd.wz / 2;
            // MBot.motor_polarity[MBot.mot_left] = -1;
            // printf("Our motor polarities are: Left: %d, Right: %d  and Wheel Base: %f\n\r", MBot.motor_polarity[MBot.mot_left], MBot.motor_polarity[MBot.mot_right], MBot.wheel_base);
            
            
            ros_mbot_motor_pwm.pwm[MBot.mot_left] = MBot.motor_polarity[MBot.mot_left] * (target_l_vel -  MBot.intercept_pos[MBot.mot_left])/MBot.slope_pos[MBot.mot_left];
            ros_mbot_motor_pwm.pwm[MBot.mot_right] = MBot.motor_polarity[MBot.mot_right] * (target_r_vel - MBot.intercept_pos[MBot.mot_right])/MBot.slope_pos[MBot.mot_right];
            ros_mbot_motor_pwm.pwm[MBot.mot_back] = 0;
            // printf("PWM values are: Left: %f, Right: %f",ros_mbot_motor_pwm.pwm[MBot.mot_left], ros_mbot_motor_pwm.pwm[MBot.mot_right]);

            if(ros_mbot_vel_cmd.vx == 0 && ros_mbot_vel_cmd.wz == 0){
                ros_mbot_motor_pwm.pwm[0] = 0;
                ros_mbot_motor_pwm.pwm[1] = 0;
                ros_mbot_motor_pwm.pwm[2] = 0;
            }
            
            // printf("Our received vx: %f, our received wz: %f \r", ros_mbot_vel_cmd.vx, ros_mbot_vel_cmd.wz);
            
            // mbot_body_vel_controller(ros_mbot_vel_cmd, ros_mbot_vel, &mbot_motor_pwm);  
        }
        else {
            drive_mode = MODE_MOTOR_PWM;
            ros_mbot_motor_pwm.utime = global_utime;
            ros_mbot_motor_pwm.pwm[0] = ros_mbot_motor_pwm_cmd.pwm[0];
            ros_mbot_motor_pwm.pwm[1] = ros_mbot_motor_pwm_cmd.pwm[1];
            ros_mbot_motor_pwm.pwm[2] = ros_mbot_motor_pwm_cmd.pwm[2];
        }

        // Set motors
        // printf("Our PWM values were: %f\t%f\t%f\r\n",ros_mbot_motor_pwm.pwm[0],ros_mbot_motor_pwm.pwm[1],ros_mbot_motor_pwm.pwm[2]);
        // printf("While our commanded velocity was: %f %f %f\r\n", ros_mbot_vel_cmd.vx, ros_mbot_vel_cmd.vy,ros_mbot_vel_cmd.wz);
        // printf("Our gains are: %f \t %f \t %f \t %f \t %f \t %f\r", MBot.forward_gain[0],MBot.forward_gain[1],MBot.forward_gain[2],MBot.turn_gain[0],MBot.turn_gain[1],MBot.turn_gain[2]);
        mbot_motor_set_duty(0, ros_mbot_motor_pwm.pwm[0]);
        mbot_motor_set_duty(1, ros_mbot_motor_pwm.pwm[1]);
        mbot_motor_set_duty(2, ros_mbot_motor_pwm.pwm[2]);

        // mbot_motor_set_duty(0, 1.0);
        // mbot_motor_set_duty(1, 1.0);
        // mbot_motor_set_duty(2, 1.0);


        // write the encoders to serial
        rcl_publish(&ROS_MBOT_ENCODER, &ros_mbot_encoder, NULL);
        // send odom on wire
        rcl_publish(&ROS_MBOT_ODOM, &ros_mbot_odom, NULL);
        // write the IMU to serial
        
// *************** We believe there's a soft cap of 5 publishers so IMU is commented out for now ********************* 
        // rcl_publish(&ROS_MBOT_IMU, &ros_mbot_imu, NULL);
        // write the Body velocity to serial
        rcl_publish(&ROS_MBOT_VEL, &ros_mbot_vel, NULL);
        // write the Motor velocity to serial
        rcl_publish(&ROS_MBOT_MOTOR_VEL, &ros_mbot_motor_vel, NULL);
        // write the PWMs to serial
        rcl_publish(&ROS_MBOT_MOTOR_PWM, &ros_mbot_motor_pwm, NULL);
        //uint64_t fn_run_len = to_us_since_boot(get_absolute_time()) + timestamp_offset - cur_pico_time;
    }
    
    // rcl_ret_t ret = rmw_uros_check_agent_status(10);
    // if(ret != RCL_RET_OK){
    //     mbot_motor_set_duty(0, 0.0);
    //     mbot_motor_set_duty(1, 0.0);
    //     mbot_motor_set_duty(2, 0.0);
    //     global_comms_status = COMMS_ERROR;
    // }

    //check comms and kill motors if its been too long
    //uint64_t timeout = to_us_since_boot(get_absolute_time()) - global_pico_time;
    // if(timeout > MBOT_TIMEOUT_US){
    //     mbot_motor_set_duty(0, 0.0);
    //     mbot_motor_set_duty(1, 0.0);
    //     mbot_motor_set_duty(2, 0.0);
    //     global_comms_status = COMMS_ERROR;
    // }

    return true;
}

void mbot_calculate_motor_vel(mbot_msg__msg__Mbotencoderst encoders, mbot_msg__msg__Mbotmotorvelt *motor_vel){
    float conversion = (1.0 / MBot.gear_ratio) * (1.0 / MBot.encoder_resolution) * 1E3f * 2.0 * M_PI;
    motor_vel->velocity[0] = MBot.encoder_polarity[0] * (conversion / encoders.delta_time) * encoders.delta_ticks[0];
    motor_vel->velocity[1] = MBot.encoder_polarity[1] * (conversion / encoders.delta_time) * encoders.delta_ticks[1];
    motor_vel->velocity[2] = MBot.encoder_polarity[2] * (conversion / encoders.delta_time) * encoders.delta_ticks[2];
}

void mbot_read_imu(mbot_msg__msg__Mbotimut *imu){
    // nothing here yet
}

void mbot_read_encoders(mbot_msg__msg__Mbotencoderst* encoders){
    int64_t delta_time = global_utime - encoders->utime;
    encoders->utime = global_utime;
    encoders->delta_time = delta_time;
    encoders->ticks[0] = mbot_encoder_read_count(0);
    encoders->ticks[1] = mbot_encoder_read_count(1);
    encoders->ticks[2] = mbot_encoder_read_count(2);
    encoders->delta_ticks[0] = mbot_encoder_read_delta(0);
    encoders->delta_ticks[1] = mbot_encoder_read_delta(1);
    encoders->delta_ticks[2] = mbot_encoder_read_delta(2);
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

int mbot_init_comms(void){
    printf("Initializing LCM serial communication...\r\n");
    if(roscomms_init() == RCL_RET_OK){
        global_comms_status = COMMS_OK;
    }
    roscomms_node_init();

    // sleep_ms(500);
    return MBOT_OK;
}

void mbot_print_state(mbot_msg__msg__Mbotimut imu, mbot_msg__msg__Mbotencoderst encoders, mbot_msg__msg__Pose2dt odometry, mbot_msg__msg__Mbotmotorvelt motor_vel){
    printf("\033[2J\r");
    if(global_comms_status == COMMS_OK){
        printf("| \033[32m COMMS OK \033[0m TIME: %lld |\n", global_utime);
    }
    else{
        printf("| \033[31m SERIAL COMMUNICATION FAILURE\033[0m     |\n");
    }
    const char* imu_headings[] = {"ROLL", "PITCH", "YAW"};
    const char* enc_headings[] = {"ENC 0", "ENC 1", "ENC 2"};
    const char* odom_headings[] = {"X", "Y", "THETA"};
    const char* motor_vel_headings[] = {"MOT 0", "MOT 1", "MOT 2"};
    // we shouldn't need to do this, need to update generateTable to handle different datatypes
    int encs[3] = {(int)ros_mbot_encoder.ticks[0], (int)ros_mbot_encoder.ticks[1], (int)ros_mbot_encoder.ticks[2]};
    char buf[1024] = {0};
    generateTableInt(buf, 1, 3, "ENCODERS", enc_headings, encs);
    printf("\r%s", buf);
    
    buf[0] = '\0';
    generateTableFloat(buf, 1, 3, "IMU", imu_headings, imu.angles_rpy);
    printf("\r%s", buf);
    
    buf[0] = '\0';
    generateTableFloat(buf, 1, 3, "MOTOR", motor_vel_headings, motor_vel.velocity);
    printf("\r%s", buf);
    
    buf[0] = '\0';
    float odom_array[3] = {odometry.x, odometry.y, odometry.theta};
    generateTableFloat(buf, 1, 3, "ODOMETRY", odom_headings, odom_array);
    printf("\r%s", buf);

    buf[0] = '\0';
    generateBottomLine(buf, 3);
    printf("\r%s\n", buf);
}

void main()
{   
    running = false;
    mbot_init_pico();
    mbot_init_hardware();
    mbot_init_comms();
    // MBot.robot_type = DIFFERENTIAL_DRIVE;
    // MBot.wheel_radius = WHEEL_RADIUS;
    // MBot.wheel_base = WHEEL_BASE;
    // MBot.gear_ratio = GEAR_RATIO;
    // MBot.encoder_resolution = ENCODER_RES;
    // MBot.motor_polarity[0] = 1;
    // MBot.motor_polarity[2] = -1;
    // MBot.encoder_polarity[0] = 1;
    // MBot.encoder_polarity[2] = -1;
    // MBot.mot_left = 0;
    // MBot.mot_right = 2;

    MBot = (mbot_params_t){DIFFERENTIAL_DRIVE,WHEEL_RADIUS,WHEEL_BASE,GEAR_RATIO,ENCODER_RES,
        0, 2, 1, {-1,1,-1}, {1,1,-1}, {0.689829,0.7,0.691755}, {-0.072841,0.0,-0.073537}, {0.684557 ,0.7,0.709771}, {-0.073214,0.0,-0.071313},
        {1.0,0.0,0.0},{1.0,0.0,0.0}};

    printf("Starting MBot Loop...\n");
    repeating_timer_t loop_timer;
    add_repeating_timer_ms(MAIN_LOOP_PERIOD * 1000, mbot_loop, NULL, &loop_timer); // 1000x to convert to ms
    
    printf("Done Booting Up!\n");
    running = true;
    uint16_t counter = 0;
    
    
    while(running){
        repeating_timer_t loop;
        roscomms_listener_loop();
        //Heartbeat
        if(!(counter % 5)){
            gpio_put(LED_PIN, 1);
        }
        else if(!(counter % 7)){
            gpio_put(LED_PIN, 1);
            counter = 0;
        }
        else{
            gpio_put(LED_PIN, 0);
        }
        // Print State
        // printf("Our received vx: %f, our received wz: %f \r", ros_mbot_vel_cmd.vx, ros_mbot_vel_cmd.wz); // this seems fine

        // mbot_print_state(ros_mbot_imu, ros_mbot_encoder, ros_mbot_odom, ros_mbot_motor_vel);
        sleep_ms(20);  
        counter++;
    }
}