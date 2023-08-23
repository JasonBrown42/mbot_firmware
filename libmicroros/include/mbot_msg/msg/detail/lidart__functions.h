// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from mbot_msg:msg/Lidart.idl
// generated code does not contain a copyright notice

#ifndef MBOT_MSG__MSG__DETAIL__LIDART__FUNCTIONS_H_
#define MBOT_MSG__MSG__DETAIL__LIDART__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "mbot_msg/msg/rosidl_generator_c__visibility_control.h"

#include "mbot_msg/msg/detail/lidart__struct.h"

/// Initialize msg/Lidart message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * mbot_msg__msg__Lidart
 * )) before or use
 * mbot_msg__msg__Lidart__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Lidart__init(mbot_msg__msg__Lidart * msg);

/// Finalize msg/Lidart message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Lidart__fini(mbot_msg__msg__Lidart * msg);

/// Create msg/Lidart message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * mbot_msg__msg__Lidart__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
mbot_msg__msg__Lidart *
mbot_msg__msg__Lidart__create();

/// Destroy msg/Lidart message.
/**
 * It calls
 * mbot_msg__msg__Lidart__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Lidart__destroy(mbot_msg__msg__Lidart * msg);

/// Check for msg/Lidart message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Lidart__are_equal(const mbot_msg__msg__Lidart * lhs, const mbot_msg__msg__Lidart * rhs);

/// Copy a msg/Lidart message.
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
mbot_msg__msg__Lidart__copy(
  const mbot_msg__msg__Lidart * input,
  mbot_msg__msg__Lidart * output);

/// Initialize array of msg/Lidart messages.
/**
 * It allocates the memory for the number of elements and calls
 * mbot_msg__msg__Lidart__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Lidart__Sequence__init(mbot_msg__msg__Lidart__Sequence * array, size_t size);

/// Finalize array of msg/Lidart messages.
/**
 * It calls
 * mbot_msg__msg__Lidart__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Lidart__Sequence__fini(mbot_msg__msg__Lidart__Sequence * array);

/// Create array of msg/Lidart messages.
/**
 * It allocates the memory for the array and calls
 * mbot_msg__msg__Lidart__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
mbot_msg__msg__Lidart__Sequence *
mbot_msg__msg__Lidart__Sequence__create(size_t size);

/// Destroy array of msg/Lidart messages.
/**
 * It calls
 * mbot_msg__msg__Lidart__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
void
mbot_msg__msg__Lidart__Sequence__destroy(mbot_msg__msg__Lidart__Sequence * array);

/// Check for msg/Lidart message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mbot_msg
bool
mbot_msg__msg__Lidart__Sequence__are_equal(const mbot_msg__msg__Lidart__Sequence * lhs, const mbot_msg__msg__Lidart__Sequence * rhs);

/// Copy an array of msg/Lidart messages.
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
mbot_msg__msg__Lidart__Sequence__copy(
  const mbot_msg__msg__Lidart__Sequence * input,
  mbot_msg__msg__Lidart__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MBOT_MSG__MSG__DETAIL__LIDART__FUNCTIONS_H_
