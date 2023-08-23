// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Particlet.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__PARTICLET__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__PARTICLET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
// Member 'parent_pose'
#include "mbot_msg/msg/detail/pose2dt__struct.h"

// Struct defined in msg/Particlet in the package mbot_msg.
typedef struct mbot_msg__msg__Particlet
{
  mbot_msg__msg__Pose2dt pose;
  mbot_msg__msg__Pose2dt parent_pose;
  double weight;
} mbot_msg__msg__Particlet;

// Struct for a sequence of mbot_msg__msg__Particlet.
typedef struct mbot_msg__msg__Particlet__Sequence
{
  mbot_msg__msg__Particlet * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Particlet__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__PARTICLET__STRUCT_H_
