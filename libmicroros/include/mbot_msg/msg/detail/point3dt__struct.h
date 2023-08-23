// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mbot_msg:msg/Point3dt.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__POINT3DT__STRUCT_H_
#define MBOT_MSG__MSG__DETAIL__POINT3DT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Point3dt in the package mbot_msg.
typedef struct mbot_msg__msg__Point3dt
{
  int64_t utime;
  float x;
  float y;
  float z;
} mbot_msg__msg__Point3dt;

// Struct for a sequence of mbot_msg__msg__Point3dt.
typedef struct mbot_msg__msg__Point3dt__Sequence
{
  mbot_msg__msg__Point3dt * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mbot_msg__msg__Point3dt__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__POINT3DT__STRUCT_H_
