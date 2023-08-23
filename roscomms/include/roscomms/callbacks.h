
// extern drive_mode;
void subscription_callback_generic(const void * msgin);
void subscription_callback_mbot_vel_cmd(const void * msgin);
void subscription_callback_mbot_motor_vel_cmd(const void * msgin);
void subscription_callback_mbot_motor_pwm_cmd(const void * msgin);
void on_parameter_changed(Parameter * param);