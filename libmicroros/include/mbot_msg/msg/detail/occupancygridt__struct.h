// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Occupancygridt.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__OCCUPANCYGRIDT__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__OCCUPANCYGRIDT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'cells'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/Occupancygridt in the package mbot_msg.
typedef struct mbot_msg__msg__Occupancygridt
{
  int64_t utime;
  float origin_x;
  float origin_y;
  float meters_per_cell;
  int32_t width;
  int32_t height;
  int32_t num_cells;
  rosidl_runtime_c__int8__Sequence cells;
} mbot_msg__msg__Occupancygridt;

// Struct for a sequence of mbot_msg__msg__Occupancygridt.
typedef struct mbot_msg__msg__Occupancygridt__Sequence
{
  mbot_msg__msg__Occupancygridt * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Occupancygridt__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__OCCUPANCYGRIDT__STRUCT_H_
