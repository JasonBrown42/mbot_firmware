#PICO_MICRO_ROS_EXAMPLE

link_directories($ENV{LIB_UROS})

add_executable(mbot
  # pico_micro_ros_latency.c
  #ros_comms_tester.c
  # pico_sub.c
  # pico_uart_transport.c
  mbot.c
  odometry.c
  print_tables.c
  # params.c
  
)

include_directories(/usr/local/include)

target_include_directories(mbot PUBLIC
  $ENV{LIB_UROS}/include
)

target_link_libraries(mbot
  pico_stdlib
  pico_multicore
  pico_time
  hardware_pwm
  hardware_sync
  hardware_i2c
  hardware_flash
  mbotlib
  rclib
  comms
  roscomms
  microros
)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

pico_enable_stdio_usb(mbot 1)
pico_enable_stdio_uart(mbot 0)

add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

pico_add_extra_outputs(mbot)
