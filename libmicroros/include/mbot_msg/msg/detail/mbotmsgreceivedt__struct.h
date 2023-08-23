// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Mbotmsgreceivedt.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__MBOTMSGRECEIVEDT__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__MBOTMSGRECEIVEDT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'channel'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/Mbotmsgreceivedt in the package mbot_msg.
typedef struct mbot_msg__msg__Mbotmsgreceivedt
{
  int64_t utime;
  int64_t creation_time;
  rosidl_runtime_c__String channel;
} mbot_msg__msg__Mbotmsgreceivedt;

// Struct for a sequence of mbot_msg__msg__Mbotmsgreceivedt.
typedef struct mbot_msg__msg__Mbotmsgreceivedt__Sequence
{
  mbot_msg__msg__Mbotmsgreceivedt * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Mbotmsgreceivedt__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__MBOTMSGRECEIVEDT__STRUCT_H_
