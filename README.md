GpioPin
=======

Simple manipulation of the GPIO pins for the Raspberry Pi.

This is a trivial project with only 3 files. You can compile it from the command line using the g++ or gcc.


Sample code (from main.cpp):



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
            // If you set up the LEDs, you will see them turning on and off
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



Compile: g++ main.cpp GpioPin.cpp  -o main

Run: sudo ./main
