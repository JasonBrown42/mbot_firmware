add_library(roscomms STATIC
    # 
    src/ros_listener.c
    src/pico_uart_transport.c
    src/callbacks.c
)

include_directories(/usr/local/include)

target_link_libraries(roscomms
  pico_stdlib
  pico_stdio_usb
  pico_multicore
  hardware_pwm
  hardware_pio
  microros
  mbotlib
)

target_include_directories(roscomms PUBLIC
  include
  $ENV{LIB_UROS}/include

)