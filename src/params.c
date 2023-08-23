#include <stdio.h>
#include <unistd.h>

// Copyright (c) 2021 - for information on the respective copyright owner
// see the NOTICE file and/or the repository https://github.com/ros2/rclc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <unistd.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <rclc_parameter/rclc_parameter.h>
#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "roscomms/ros_listener.h"

const uint LED_PIN = 25;

rclc_parameter_server_t param_server;
const rclc_parameter_options_t options = {
    .notify_changed_over_dds = false,
    .max_params = 20
};

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
  (void) timer;
  (void) last_call_time;

  int value;
  rclc_parameter_get_int(&param_server, "param2", &value);
  value++;
  rclc_parameter_set_int(&param_server, "param2", (int64_t) value);
  printf("%d\n",value);
}

void on_parameter_changed(Parameter * param)
{
//   printf("Parameter %s modified.", param->name.data);
//   switch (param->value.type) {
//     case RCLC_PARAMETER_BOOL:
//       printf(" New value: %d (bool)", param->value.bool_value);
//       break;
//     case RCLC_PARAMETER_INT:
//       printf(" New value: %ld (int)", param->value.integer_value);
//       break;
//     case RCLC_PARAMETER_DOUBLE:
//       printf(" New value: %f (double)", param->value.double_value);
//       break;
//     default:
//       break;
//   }
//   printf("\n");
  return;
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

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
  rcl_ret_t rc;
  rcl_allocator_t allocator = rcl_get_default_allocator();

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;

    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);


  // Create init_options
  rclc_support_t support;
  rclc_support_init(&support, 0, NULL, &allocator);

  // Create node
  rcl_node_t node;
  rclc_node_init_default(&node, "demo_param_node", "", &support);

  // Create parameter service
  rclc_parameter_server_init_with_option(&param_server, &node, &options);

  // create timer,
  rcl_timer_t timer;
  rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(1000),
    timer_callback);

  // Create executor
  rclc_executor_t executor;
  rclc_executor_init(
    &executor, &support.context, RCLC_PARAMETER_EXECUTOR_HANDLES_NUMBER + 1,
    &allocator);
  rclc_executor_add_parameter_server(&executor, &param_server, on_parameter_changed);
  rclc_executor_add_timer(&executor, &timer);

  // Add parameters
  rclc_add_parameter(&param_server, "param1", RCLC_PARAMETER_BOOL);
  rclc_add_parameter(&param_server, "param2", RCLC_PARAMETER_INT);
  rclc_add_parameter(&param_server, "param3", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param4", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param5", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param6", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param7", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param8", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param9", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param10", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param11", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param12", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param13", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param14", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param15", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param16", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param17", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param18", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param19", RCLC_PARAMETER_DOUBLE);
  rclc_add_parameter(&param_server, "param20", RCLC_PARAMETER_DOUBLE);
    
//   rclc_parameter_set_bool(&param_server, "param1", false);
//   rclc_parameter_set_int(&param_server, "param2", 10);
//   rclc_parameter_set_double(&param_server, "param3", 0.01);

//   bool param1;
//   int param2;
//   double param3;

//   rclc_parameter_get_bool(&param_server, "param1", &param1);
//   rclc_parameter_get_int(&param_server, "param2", &param2);
//   rclc_parameter_get_double(&param_server, "param3", &param3);

 
    // msg.data = 0;
    while (true)
    {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    }
    return 0;
}