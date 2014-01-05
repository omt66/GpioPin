/* 
 * File:    main.cpp
 * Author:  Ogun TIGLI 
 * Email:   omt66@hotmail.com
 * License: MIT (see http://opensource.org/licenses/MIT)
 * 
 * Created on January 4, 2014, 10:09 PM
 */

#include <iostream>
#include <unistd.h>
#include "GpioPin.h"

using namespace std;


/**
 * A convenience function to wait (sleep) for a while based on the provided
 * input value.
 * 
 * @param milliseconds
 */
void wait(int milliseconds) {
    usleep(milliseconds*1000);
}

/**
 * Simple demo for the GPIO library.
 * 
 */
int main(int argc, char** argv) {
    try {
        cout << "--- GPIO Test by Ogun (4 Jan 2014/Sat) ---" << endl;
        GpioPin p1(4);
        GpioPin p2(17);
        GpioPin p3(18);
        
        p1.setAsOutput();
        p2.setAsOutput();
        p3.setAsOutput();

        // Let's turn on and off the outputs!
        // If you set up the LEDs, you will see them turning on and off based on 
        // based on the GPIO pins' output values.
        for (int i=0;i < 100;i++) {
            p1.setValue(i % 2 == 0 ? 1 : 0);
            p2.setValue(i % 4 == 0 ? 1 : 0);
            p3.setValue(i % 8 == 0 ? 1 : 0);
            wait(500);
        }
        
        cout << "--- Done ---" << endl;
    }
    catch (string exceptionStr){
        cout << "Exception: " << exceptionStr << endl;
        return -1;
    }
    
    return 0;
}

