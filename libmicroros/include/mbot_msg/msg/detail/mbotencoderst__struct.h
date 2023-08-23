// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Mbotencoderst.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__MBOTENCODERST__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__MBOTENCODERST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Mbotencoderst in the package mbot_msg.
typedef struct mbot_msg__msg__Mbotencoderst
{
  int64_t utime;
  int64_t ticks[3];
  int32_t delta_ticks[3];
  int32_t delta_time;
} mbot_msg__msg__Mbotencoderst;

// Struct for a sequence of mbot_msg__msg__Mbotencoderst.
typedef struct mbot_msg__msg__Mbotencoderst__Sequence
{
  mbot_msg__msg__Mbotencoderst * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Mbotencoderst__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__MBOTENCODERST__STRUCT_H_
