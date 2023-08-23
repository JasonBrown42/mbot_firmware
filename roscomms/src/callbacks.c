#include <roscomms/ros_listener.h>
#include <roscomms/callbacks.h>
#include <string.h>

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
    // printf("%f %f \r", vel_cmd.linear.x, vel_cmd.angular.z); // even this is good
    // printf(" %f %f\r", msg_->linear.x, msg_->angular.z); // this is good
}

void subscription_callback_mbot_motor_vel_cmd(const void * msgin)
{ 
    drive_mode = MODE_MOTOR_VEL;

}

void subscription_callback_mbot_motor_pwm_cmd(const void * msgin)
{ 
    drive_mode = MODE_MOTOR_PWM;
}

void on_parameter_changed(Parameter * param)
{
//   printf("Parameter %s modified.", param->name.data);
//   switch (param->name.data) {
    // case "FORWARD_KP":
    // printf("\r\n\n");
    // printf(param->name.data);
    // printf("\t");
    // printf("%f ",param->value.double_value);
    // // MBot.forward_gain[0] = param->value.double_value;
    // printf("\n\r\n");
      if(!strcmp(param->name.data, "FORWARD_KP")){
        MBot.forward_gain[0] = param->value.double_value;
      }else if(!strcmp(param->name.data, "FORWARD_KI")){
        MBot.forward_gain[1] = param->value.double_value;
      }else if(!strcmp(param->name.data, "FORWARD_KD")){
        MBot.forward_gain[2] = param->value.double_value;
      }
      
      else if(!strcmp(param->name.data, "TURN_KP")){
        MBot.turn_gain[0] = param->value.double_value;
      }else if(!strcmp(param->name.data, "TURN_KI")){
        MBot.turn_gain[1] = param->value.double_value;
      }else if(!strcmp(param->name.data, "TURN_KD")){
        MBot.turn_gain[2] = param->value.double_value;
      }
      
      else if(!strcmp(param->name.data, "LEFT_FORWARD_M")){
        MBot.slope_pos[MBot.mot_left] = param->value.double_value;
      }else if(!strcmp(param->name.data, "LEFT_FORWARD_B")){
        MBot.intercept_pos[MBot.mot_left] = param->value.double_value;
      }else if(!strcmp(param->name.data, "LEFT_BACKWARD_M")){
        MBot.slope_neg[MBot.mot_left] = param->value.double_value;
      }else if(!strcmp(param->name.data, "LEFT_BACKWARD_B")){
        MBot.intercept_neg[MBot.mot_left] = param->value.double_value;
      }
      
      else if(!strcmp(param->name.data, "RIGHT_FORWARD_M")){
        MBot.slope_pos[MBot.mot_right] = param->value.double_value;
      }else if(!strcmp(param->name.data, "RIGHT_FORWARD_B")){
        MBot.intercept_pos[MBot.mot_right] = param->value.double_value;
      }else if(!strcmp(param->name.data, "RIGHT_BACKWARD_M")){
        MBot.slope_neg[MBot.mot_right] = param->value.double_value;
      }else if(!strcmp(param->name.data, "RIGHT_BACKWARD_B")){
        MBot.intercept_neg[MBot.mot_right] = param->value.double_value;
      }
      
      else if(!strcmp(param->name.data, "ENCODER_POLARITY_LEFT")){
        MBot.encoder_polarity[MBot.mot_left] = param->value.double_value;
      }else if(!strcmp(param->name.data, "ENCODER_POLARITY_RIGHT")){
        MBot.encoder_polarity[MBot.mot_right] = param->value.double_value;
      }
      
      else if(!strcmp(param->name.data, "MOTOR_POLARITY_LEFT")){
        MBot.motor_polarity[MBot.mot_left] = param->value.double_value;
      }else if(!strcmp(param->name.data, "MOTOR_POLARITY_RIGHT")){
        MBot.motor_polarity[MBot.mot_right] = param->value.double_value;
      }
      
      else if(!strcmp(param->name.data, "WHEEL_BASE")){
        MBot.wheel_base = param->value.double_value;
      }else if(!strcmp(param->name.data, "WHEEL_RADIUS")){
        MBot.wheel_radius = param->value.double_value;
      }
  
  return;
}