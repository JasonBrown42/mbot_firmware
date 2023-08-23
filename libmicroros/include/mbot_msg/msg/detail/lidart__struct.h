// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Lidart.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__LIDART__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__LIDART__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'ranges'
// Member 'thetas'
// Member 'times'
// Member 'intensities'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/Lidart in the package mbot_msg.
typedef struct mbot_msg__msg__Lidart
{
  int64_t utime;
  int32_t num_ranges;
  rosidl_runtime_c__float__Sequence ranges;
  rosidl_runtime_c__float__Sequence thetas;
  rosidl_runtime_c__int64__Sequence times;
  rosidl_runtime_c__float__Sequence intensities;
} mbot_msg__msg__Lidart;

// Struct for a sequence of mbot_msg__msg__Lidart.
typedef struct mbot_msg__msg__Lidart__Sequence
{
  mbot_msg__msg__Lidart * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Lidart__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__LIDART__STRUCT_H_
