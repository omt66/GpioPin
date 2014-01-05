/* 
 * File:    GpioPin.cpp
 * Author:  Ogun TIGLI 
 * Email:   omt66@hotmail.com
 * License: MIT (see http://opensource.org/licenses/MIT)
 * 
 * Created on January 4, 2014, 10:09 PM
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "GpioPin.h"

using namespace std;

/**
 * Main constructor for the GpioPin class. It requires the GPIO pin number.
 * For Raspberry PI, description for the GPIO pins can be found in the 
 * following URL: http://elinux.org/RPi_Low-level_peripherals
 * 
 * Valid pins for the input/output: 4, 17, 18, 22, 23, 24, 25, 27 (other pins 
 * are used for I2C SDA, SCL, UART TXD, RXD, SPI, PCM out, etc.) 
 * 
 * @param gpioPinNo
 */
GpioPin::GpioPin(int gpioPinNo) {
    mGpioPinNo = gpioPinNo;
    mInitialized = false;
    
    gpioExport();
}

/**
 * Copy constructor for this class.
 * @param orig original instance to be copied
 */
GpioPin::GpioPin(const GpioPin& orig) {
    mGpioPinNo = orig.mGpioPinNo;
    mOn = orig.mOn;
    mDirectionIsOutput = orig.mDirectionIsOutput;
    mInitialized = orig.mInitialized;
}

/**
 * Destructor for the IOPin class.
 */
GpioPin::~GpioPin() {
    gpioUnexport();
}

/**
 * Sets the GPIO pin as input.
 */
void GpioPin::setAsInput() {
    setGpioDirection(DIRECTION_IN);
}

/**
 * Sets the GPIO pin as output.
 */
void GpioPin::setAsOutput() {
    setGpioDirection(DIRECTION_OUT);
}

/**
 * A convenience method to turn the pin output high (1)
 */
void GpioPin::turnOn() {
    setGpioValue(1);
}

/**
 * A convenience method to turn the pin output low (0)
 */
void GpioPin::turnOff() {
    setGpioValue(0);
}

/**
 * Finds out whether the pin is on (i.e. high or low)
 * 
 * @return the current status of the output pin
 */
bool GpioPin::isOn() {
    return mOn;
}

/**
 * Gets the value for the GPIO pin. It throws an exception if the pin is
 * an output pin.
 * 
 * @return current value of the GPIO pin
 */
int GpioPin::getValue() {   
    if (mDirectionIsOutput) {
        stringstream ss;
        ss << "The GPIO pin " 
           << mGpioPinNo 
           << " is set for output, its value cannot be read!";

        throw ss.str();
    }
    
    return getGpioValue();
}

/**
 * Sets the value for the GPIO pin. It throws an exception if the pin is
 * an output pin. It also throws an exception if the value is not acceptable.
 * 
 * @param value
 */
void GpioPin::setValue(int value) {
    if (!mDirectionIsOutput) {
        stringstream ss;
        ss << "The GPIO pin " 
           << mGpioPinNo 
           << " is set for output, its value cannot be set!";

        throw ss.str();
    }
    
    if (value != 0 && value != 1) {
        stringstream ss;
        ss << "The digital output value for the GPIO pin "
           << mGpioPinNo
           << " should be either 0 or 1.";

        throw ss.str();
    }
    
    setGpioValue(value);
}

/**
 * Checks whether the GPIO pin initialized or not. If it is not initialized
 * then this method will throw an exception.
 */
void GpioPin::checkInitialization() {
    if (!mInitialized) {
        stringstream ss;
        ss << "The GPIO pin " 
           << mGpioPinNo 
           << " is not initialized as an input or output yet!";

        throw ss.str();
    }
}

/**
 * Sets the GPIO pin (exports it).
 */
void GpioPin::gpioExport() {
    string path = "/sys/class/gpio/export";
    ofstream os(path.c_str());
    os << mGpioPinNo;
    os.close();
}

/**
 * Sets the GPIO pin (unexports it).
 */
void GpioPin::gpioUnexport() {
    string path = "/sys/class/gpio/unexport";
    ofstream os(path.c_str());
    os << mGpioPinNo;
    os.close();
}

/**
 * Sets the direction for the GPIO pin (either input or output)
 * @param direction
 */
void GpioPin::setGpioDirection(string direction) {
    mInitialized = true;
    mOn = false;
    
    if (direction == DIRECTION_OUT)
        mDirectionIsOutput = true;
    else
        mDirectionIsOutput = false;
    
    stringstream ss;
    ss << "/sys/class/gpio/gpio" << mGpioPinNo << "/direction";
    ofstream ofs(ss.str().c_str());
    ofs << direction;
    ofs.close();
}

/**
 * Sets the value for the GPIO pin.
 * 
 * @param value
 */
void GpioPin::setGpioValue(int value) {
    checkInitialization();
    
    if (value == 1)
        mOn = true;
    else
        mOn = false;
    
    stringstream ss;
    ss << "/sys/class/gpio/gpio" << mGpioPinNo << "/value";    
    ofstream ofs(ss.str().c_str());
    ofs << value;
    ofs.close();
}

/**
 * Gets the value for the GPIO pin.
 * 
 * @return current value
 */
int GpioPin::getGpioValue() {
    checkInitialization();
    
    int value = 0;    
    
    stringstream ss;
    ss << "/sys/class/gpio/gpio" << mGpioPinNo << "/value";
    ifstream ifs(ss.str().c_str());
    ifs >> value;
    ifs.close();
    
    if (value == 1)
        mOn = true;
    else
        mOn = false;
    
    return value;
}

// Initialize the static constant values
const string GpioPin::DIRECTION_IN  = "in";
const string GpioPin::DIRECTION_OUT = "out";




