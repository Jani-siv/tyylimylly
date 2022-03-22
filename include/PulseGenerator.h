#pragma once
#include "GpioPins.h"
#include <map>
#include <unistd.h>
#define OUT true

class PulseGenerator{
    public:
        PulseGenerator(char* device, int outputPin);
        ~PulseGenerator();
        void generateRps(int pulseOnMills, int timesInsec, int seconds);
    private:
        char *dev = nullptr;
        int activeOutputPin = 0; 
        GpioPins* pin;
};
