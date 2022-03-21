#include "../include/GpioPins.h"
#include <linux/gpio.h>
#include <sys/ioctl.h>

GpioPins::GpioPins()
{

}

GpioPins::~GpioPins()
{

}
void GpioPins::initPins(std::map<int,bool>&pinNumbers, char *device)
{
    int fd, ret;
    fd = open(device, O_RDONLY);
        if (fd < 0)
        {
            std::cerr<<"error open device"<<std::endl;
            exit(-1);
        }
    
    for(auto const& [pin, dire] : pinNumbers) 
    {
        this->setPinDirection(pin, dire);
    }
    ret = ioctl(fd,GPIO_GET_LINEHANDLE_IOCTL,&this->output);
    if (ret < 0)
    {
        std::cerr<<"Error to init output pins"<<std::endl;
        exit(-1);
    }
    ret = ioctl(fd,GPIO_GET_LINEHANDLE_IOCTL,&this->input);
    if (ret < 0)
    {
        std::cerr<<"Error to init input pins"<<std::endl;
        exit(-1);
    }

}

void GpioPins::writeBit(int pin, bool state)
{
    int ret;
    if (state == false)
    {
        this->outputdata.values[0] = 0;
    }
    else
    {
        this->outputdata.values[0] = 255;
    }

    ret = ioctl(this->output.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &this->outputdata);
    if (ret < 0)
    {
        std::cerr<<"Error change pin state"<<std::endl;
        exit(-1);
    }

}

void GpioPins::setPinDirection(int datapin, bool direction)
{
    if (direction == OUT)
    {
        this->output.lineoffsets[this->useOut] = datapin;
        this->output.flags = GPIOHANDLE_REQUEST_OUTPUT;
        memcpy(this->output.default_values, &this->outputdata, sizeof(this->output.default_values));
        this->useOut++;
        this->output.lines = this->useOut;
    }
    else
    {
        this->input.lineoffsets[this->useIn] = datapin;
        this->input.flags = GPIOHANDLE_REQUEST_INPUT;
        memcpy(this->input.default_values,&this->inputdata,sizeof(this->input.default_values));
        this->useIn++;
        this->input.lines = this->useIn;
    }

}
