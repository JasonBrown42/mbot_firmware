// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Joyt.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__JOYT__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__JOYT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Joyt in the package mbot_msg.
typedef struct mbot_msg__msg__Joyt
{
  int64_t timestamp;
  float left_analog_x;
  float left_analog_y;
  float right_analog_x;
  float right_analog_y;
  float right_trigger;
  float left_trigger;
  float dpad_x;
  float dpad_y;
  int8_t button_a;
  int8_t button_b;
  int8_t button_2;
  int8_t button_x;
  int8_t button_y;
  int8_t button_5;
  int8_t button_l1;
  int8_t button_r1;
  int8_t button_l2;
  int8_t button_r2;
  int8_t button_select;
  int8_t button_start;
  int8_t button_12;
  int8_t button_left_analog;
  int8_t button_right_analog;
  int8_t button_15;
} mbot_msg__msg__Joyt;

// Struct for a sequence of mbot_msg__msg__Joyt.
typedef struct mbot_msg__msg__Joyt__Sequence
{
  mbot_msg__msg__Joyt * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Joyt__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__JOYT__STRUCT_H_
