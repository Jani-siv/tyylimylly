#include "../include/PulseGenerator.h"

PulseGenerator::PulseGenerator(char* device, int outputPin)
{
    this->dev = device;
    GpioPins pinned;
    this->activeOutputPin = outputPin;
    std::map<int,bool>outputPinMap;
    //outputPinMap[outputPin] = OUT;
    outputPinMap[17] = IN;
    outputPinMap[27] = OUT;
    this->pin.initPins(outputPinMap, this->dev);
}
PulseGenerator::~PulseGenerator()
{

}

void PulseGenerator::generateRps(int pulseOnMills, int timesInsec, int seconds)
{
    if ((pulseOnMills * timesInsec) > 1000)
    {
        std::cerr<<"Pulse ON time is bigger than second"<<std::endl;
        exit(-1);
    }
    int mills = 1000;
    int offtime = mills - pulseOnMills * timesInsec;
    int pulseOff = offtime / timesInsec;
    for ( int i = 0; i < seconds; i++)
    {
     for ( int k = 0; k < timesInsec; k++)
     {
        this->pin.writeBit(1, true);
        usleep((pulseOnMills*1000));
        this->pin.writeBit(1, false);
        usleep((pulseOff*1000));
     }
    }
}
