// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Path2dt.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__PATH2DT__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__PATH2DT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'path'
#include "mbot_msg/msg/detail/pose2dt__struct.h"

// Struct defined in msg/Path2dt in the package mbot_msg.
typedef struct mbot_msg__msg__Path2dt
{
  int64_t utime;
  int32_t path_length;
  mbot_msg__msg__Pose2dt__Sequence path;
} mbot_msg__msg__Path2dt;

// Struct for a sequence of mbot_msg__msg__Path2dt.
typedef struct mbot_msg__msg__Path2dt__Sequence
{
  mbot_msg__msg__Path2dt * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Path2dt__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__PATH2DT__STRUCT_H_
