// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from mbot_msg:msg/Joyt.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__JOYT__FUNCTIONS_H_
#define MBOT_MSG__MSG__DETAIL__JOYT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "mbot_msg/msg/rosidl_generator_c__visibility_control.h"

#include "mbot_msg/msg/detail/joyt__struct.h"

/// Initialize msg/Joyt message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * mbot_msg__msg__Joyt
 * )) before or use
 * mbot_msg__msg__Joyt__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Joyt__init(mbot_msg__msg__Joyt * msg);

/// Finalize msg/Joyt message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Joyt__fini(mbot_msg__msg__Joyt * msg);

/// Create msg/Joyt message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * mbot_msg__msg__Joyt__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
mbot_msg__msg__Joyt *
mbot_msg__msg__Joyt__create();

/// Destroy msg/Joyt message.
/**
 * It calls
 * mbot_msg__msg__Joyt__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Joyt__destroy(mbot_msg__msg__Joyt * msg);

/// Check for msg/Joyt message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Joyt__are_equal(const mbot_msg__msg__Joyt * lhs, const mbot_msg__msg__Joyt * rhs);

/// Copy a msg/Joyt message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Joyt__copy(
  const mbot_msg__msg__Joyt * input,
  mbot_msg__msg__Joyt * output);

/// Initialize array of msg/Joyt messages.
/**
 * It allocates the memory for the number of elements and calls
 * mbot_msg__msg__Joyt__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Joyt__Sequence__init(mbot_msg__msg__Joyt__Sequence * array, size_t size);

/// Finalize array of msg/Joyt messages.
/**
 * It calls
 * mbot_msg__msg__Joyt__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Joyt__Sequence__fini(mbot_msg__msg__Joyt__Sequence * array);

/// Create array of msg/Joyt messages.
/**
 * It allocates the memory for the array and calls
 * mbot_msg__msg__Joyt__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
mbot_msg__msg__Joyt__Sequence *
mbot_msg__msg__Joyt__Sequence__create(size_t size);

/// Destroy array of msg/Joyt messages.
/**
 * It calls
 * mbot_msg__msg__Joyt__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Joyt__Sequence__destroy(mbot_msg__msg__Joyt__Sequence * array);

/// Check for msg/Joyt message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Joyt__Sequence__are_equal(const mbot_msg__msg__Joyt__Sequence * lhs, const mbot_msg__msg__Joyt__Sequence * rhs);

/// Copy an array of msg/Joyt messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Joyt__Sequence__copy(
  const mbot_msg__msg__Joyt__Sequence * input,
  mbot_msg__msg__Joyt__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__JOYT__FUNCTIONS_H_
