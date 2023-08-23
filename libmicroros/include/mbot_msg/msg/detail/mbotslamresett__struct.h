// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Mbotslamresett.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__MBOTSLAMRESETT__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__MBOTSLAMRESETT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'slam_map_location'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/Mbotslamresett in the package mbot_msg.
typedef struct mbot_msg__msg__Mbotslamresett
{
  int64_t utime;
  int32_t slam_mode;
  rosidl_runtime_c__String slam_map_location;
  bool retain_pose;
} mbot_msg__msg__Mbotslamresett;

// Struct for a sequence of mbot_msg__msg__Mbotslamresett.
typedef struct mbot_msg__msg__Mbotslamresett__Sequence
{
  mbot_msg__msg__Mbotslamresett * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Mbotslamresett__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__MBOTSLAMRESETT__STRUCT_H_
