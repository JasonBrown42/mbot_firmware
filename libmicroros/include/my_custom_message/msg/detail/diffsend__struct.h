// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_custom_message:msg/Diffsend.idl
// generated code does not contain a copyright notice

#ifndef MY_CUSTOM_MESSAGE__MSG__DETAIL__DIFFSEND__STRUCT_H_
#define MY_CUSTOM_MESSAGE__MSG__DETAIL__DIFFSEND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Diffsend in the package my_custom_message.
typedef struct my_custom_message__msg__Diffsend
{
  uint32_t uint32_test;
  int64_t int64_test;
  uint64_t uint64_test;
} my_custom_message__msg__Diffsend;

// Struct for a sequence of my_custom_message__msg__Diffsend.
typedef struct my_custom_message__msg__Diffsend__Sequence
{
  my_custom_message__msg__Diffsend * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_custom_message__msg__Diffsend__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_CUSTOM_MESSAGE__MSG__DETAIL__DIFFSEND__STRUCT_H_
