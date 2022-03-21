#include <iostream>
#include "../include/GpioPins.h"
#include <map>
int main()
{
    std::map<int,bool> pins;
    pins[17] = false;
    pins[27] = true;
    char dev[] = "/dev/gpiochip0";
    GpioPins localPin;
    char* device;
    device = dev;
    localPin.initPins(pins, device);
    std::cout<<"hello world"<<std::endl;
    return 0;
}

