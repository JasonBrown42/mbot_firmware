// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Particlest.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__PARTICLEST__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__PARTICLEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'particles'
#include "mbot_msg/msg/detail/particlet__struct.h"

// Struct defined in msg/Particlest in the package mbot_msg.
typedef struct mbot_msg__msg__Particlest
{
  int64_t utime;
  int32_t num_particles;
  mbot_msg__msg__Particlet__Sequence particles;
} mbot_msg__msg__Particlest;

// Struct for a sequence of mbot_msg__msg__Particlest.
typedef struct mbot_msg__msg__Particlest__Sequence
{
  mbot_msg__msg__Particlest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Particlest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__PARTICLEST__STRUCT_H_
