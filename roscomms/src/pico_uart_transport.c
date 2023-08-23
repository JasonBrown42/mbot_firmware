#include <stdio.h>
#include "pico/stdlib.h"
#include <pico/stdio_usb.h>


#include <uxr/client/profile/transport/custom/custom_transport.h>

void usleep(uint64_t us)
{
    sleep_us(us);
}

int clock_gettime(clockid_t unused, struct timespec *tp)
{
    uint64_t m = time_us_64();
    tp->tv_sec = m / 1000000;
    tp->tv_nsec = (m % 1000000) * 1000;
    return 0;
}

bool pico_serial_transport_open(struct uxrCustomTransport * transport)
{
    stdio_init_all();
    return true;
}

bool pico_serial_transport_close(struct uxrCustomTransport * transport)
{
    return true;
}

size_t pico_serial_transport_write(struct uxrCustomTransport * transport, uint8_t *buf, size_t len, uint8_t *errcode)
{
    stdio_usb_out_chars_itf(1, buf, len);

    // Original Uart transport protocol (modifying for ROS on ttyACM1)
    // for (size_t i = 0; i < len; i++)
    // {
    //     if (buf[i] != putchar(buf[i]))
    //     {
    //         *errcode = 1;
    //         return i;
    //     }
    // }
    return len;
}

size_t pico_serial_transport_read(struct uxrCustomTransport * transport, uint8_t *buf, size_t len, int timeout, uint8_t *errcode)
{
    // this part is creating teh delay !!
    uint64_t start_time_us = time_us_64();
    while(tud_cdc_n_available(1) < (len)) //+1
    {
        //spin until the full set of message bytes have arrived
        int64_t elapsed_time_us = timeout * 1000 - (time_us_64() - start_time_us);
        if (elapsed_time_us < 0)
        {
            *errcode = 1;
            return 0;
        }
        
    }
    // till here
    int rc = stdio_usb_in_chars_itf(1, buf, len);
    
   


    // Original Uart transport protocol (modifying for ROS on ttyACM1)
    // uint64_t start_time_us = time_us_64();
    // for (size_t i = 0; i < len; i++)
    // {
    //     int64_t elapsed_time_us = timeout * 1000 - (time_us_64() - start_time_us);
    //     if (elapsed_time_us < 0)
    //     {
    //         *errcode = 1;
    //         return i;
    //     }

    //     int character = getchar_timeout_us(elapsed_time_us);
    //     if (character == PICO_ERROR_TIMEOUT)
    //     {
    //         *errcode = 1;
    //         return i;
    //     }
    //     buf[i] = character;
    // }
    return len;
}
