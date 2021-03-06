#pragma once
#include <iostream>
#include <linux/gpio.h>
#include <map>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#define OUT true
#define IN false

class GpioPins{
    public:
        GpioPins();
        ~GpioPins();
        void initPins(std::map<int,bool>&pinNumbers,char *device);
        void writeBit(int pin, bool state);
    private:
        int useOut = 0;
        int useIn = 0;
        void setPinDirection(int datapin, bool direction);
        struct gpiohandle_data outputdata, inputdata;
        struct gpiohandle_request input, output;
};
