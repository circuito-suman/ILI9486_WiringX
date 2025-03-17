/* similar approach using https://github.com/sonicpp/ili9486/blob/master/stm32f4/main.c
&
https://github.com/way5/ili9486-driver-for-stm32-hal*/

#include <driver.h>
#include "wiringX.h"
#include <iostream>

int fd_spi;
void init_ili9486(const int code[]);

int main(void)
{
    wiringX::wiringXsetup();
    init_ili9486(ili9486_init);
    wiringX::pinMode(0, OUTPUT);
    // test blink code
    for (int i = 0; i < 5; i++)
    {
        wiringX::digitalWrite(0, HIGH);
        wiringX::delay(1000);
        wiringX::digitalWrite(0, LOW);
        wiringX::delay(1000);
    }
    //
    // test spi code
    if ((fd_spi = wiringX::wiringXSPISetup(SPI_CHAN, SPI_SPEED)) < 0)
    {
        std::cout << "SPI Setup failed with error code:" << fd_spi << std::endl;
    }
    else
    {
        std::cout << "SPI Setup successful" << fd_spi << std::endl;
    }

    while (1)
    {
    }

    return 0;
}

void init_ili9486(const int code[])
{
    int done = 0;
    int const *cmd = ili9486_init;
    int is_cmd = 0;
    /* yet to write the reset lcd part */

    // Set reset pin high
    digitalWrite(rs_pin, HIGH);

    // Set reset pin low
    digitalWrite(rs_pin, LOW);

    // Set reset pin high again
    digitalWrite(rs_pin, HIGH);

    while (!done)
    {
        switch (*cmd)
        {
        case -1:
            is_cmd = 1;
            break;
        case -2:
            wiringX::delay(*(cmd + 1));
            break;
        case -3:
            done = 1;
            break;
        default:
            if (is_cmd)
            {
                // alternate to SendCmd((uint16_t) *cmd);
                is_cmd = 0;
            }
            else
            {
                // alternate to SendData((uint16_t) *cmd);
            }
            break;
        }
        cmd += 1;
    }
}
