#include <driver.h>
#include "wiringX.h"
#include <iostream>

int main(void)
{
    wiringX::init();
    wiringX::pinMode(1, OUTPUT);
    wiringX::digitalWrite(1, HIGH);
    wiringX::delay(1000);
    wiringX::digitalWrite(1, LOW);
    wiringX::delay(1000);
    wiringX::deinit();
    return 0;
}
