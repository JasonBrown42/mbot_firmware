// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Mbotimut.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__MBOTIMUT__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__MBOTIMUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Mbotimut in the package mbot_msg.
typedef struct mbot_msg__msg__Mbotimut
{
  int64_t utime;
  float gyro[3];
  float accel[3];
  float mag[3];
  float angles_rpy[3];
  float angles_quat[4];
  float temp;
} mbot_msg__msg__Mbotimut;

// Struct for a sequence of mbot_msg__msg__Mbotimut.
typedef struct mbot_msg__msg__Mbotimut__Sequence
{
  mbot_msg__msg__Mbotimut * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Mbotimut__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__MBOTIMUT__STRUCT_H_
