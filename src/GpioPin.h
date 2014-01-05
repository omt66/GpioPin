/* 
 * File:    GpioPin.h
 * Author:  Ogun TIGLI 
 * Email:   omt66@hotmail.com
 * License: MIT (see http://opensource.org/licenses/MIT)
 * 
 * Created on January 4, 2014, 10:09 PM
 */

#ifndef OT_RPI_GPIOPIN_H
#define	OT_RPI_GPIOPIN_H

#include <string>

using namespace std;

/*
 * Intention of this class is to provide a simple way to access to the GPIO pins
 * in the Raspberry Pi. GPIO pins are general purpose pins that can be set as 
 * either input or output pin.
 * 
 * This class uses Linux virtual file system (sysfs). Sysfs exports the related
 * information about the devices (and their drivers) to the kernel device model,
 * and allows us to access them as a file system.
 * 
 */
class GpioPin {
public:
    GpioPin(int gpioPinNo);
    GpioPin(const GpioPin& orig);
    virtual ~GpioPin();

    //--- Public Methods ---
    void setAsInput();
    void setAsOutput();
    void turnOn();
    void turnOff();
    bool isOn();
    int  getValue();
    void setValue(int value);

private:
    //--- Data Members ---
    int  mGpioPinNo;
    bool mOn;
    bool mDirectionIsOutput;
    bool mInitialized;
    
    static const string DIRECTION_IN;
    static const string DIRECTION_OUT;
    
    //--- Private Methods ---
    void checkInitialization();
    void gpioExport();
    void gpioUnexport();
    void setGpioDirection(string direction);
    void setGpioValue(int value);
    int  getGpioValue();
    
};

#endif	

