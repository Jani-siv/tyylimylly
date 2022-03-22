#include <iostream>
#include "../include/GpioPins.h"
#include "../include/PulseGenerator.h"
#include <map>
#define IN false
#define OUT true
#define HIGH true
#define LOW false

int main()
{
    std::map<int,bool> pins;
    pins[17] = IN;
    pins[27] = OUT;
    char dev[] = "/dev/gpiochip0";
    GpioPins localPin;
    char* device;
    device = dev;
    PulseGenerator pulse(dev,27);
    pulse.generateRps(10, 20, 3);
/*
    localPin.initPins(pins, device);
    while(1)
    {
    localPin.writeBit(1, HIGH);
    sleep(1);
    localPin.writeBit(1, LOW);
    sleep(1);
    }
*/
    std::cout<<"hello world"<<std::endl;
    return 0;
}

