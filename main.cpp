#include "mbed.h"
#include "arm_book_lib.h"

DigitalIn driverSeat(D2);
DigitalIn driverSeatBelt(D4);
DigitalIn passengerSeat(D3);
DigitalIn passengerSeatBelt(D5);
DigitalIn ignition(D6);
DigitalOut ignitionEnabled(LED1);
DigitalOut engineStarted(LED2);
DigitalInOut buzzerPin(PE_10);
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

bool driverSeatState = OFF;
bool ignitionState = OFF;
bool ignitionEnabledState = OFF;
bool done = OFF;


void inputsInit();
void outputsInit();
void updateDriverSitting();
void updateReadyToDrive();
void updateEngineStarted();

int main()
{
    inputsInit();
    outputsInit();

    while (!done) {
        updateDriverSitting();
        updateReadyToDrive();
        updateEngineStarted();

        }
    
}

void inputsInit()
{
    driverSeat.mode(PullDown);
    driverSeatBelt.mode(PullDown);
    passengerSeat.mode(PullDown);
    passengerSeatBelt.mode(PullDown);
    ignition.mode(PullDown);
    buzzerPin.mode(OpenDrain);
    buzzerPin.input();
}

void outputsInit()
{
    ignitionEnabled = OFF;
    engineStarted = OFF;
} 

void updateDriverSitting()
{
    if (!driverSeatState && driverSeat){
        uartUsb.write("Welcome to enhanced alarm system model 218-W24.\r\n", 49);
        driverSeatState = ON;
    }

    if (!driverSeat){
        driverSeatState = OFF;
    }
}

void updateReadyToDrive()
{
    if (!ignitionState){
        if(driverSeat && passengerSeat && driverSeatBelt && passengerSeatBelt){
            ignitionEnabledState = ON;
        }
        else{
            ignitionEnabledState = OFF;
        }
        ignitionEnabled = ignitionEnabledState;
    }
}

void updateEngineStarted()
{
    if (ignition){
        if (ignitionEnabled){
            if (ignitionEnabledState){
                uartUsb.write("Engine started.\r\n", 17);
                engineStarted = ON;
                ignitionEnabled = OFF;
                ignitionState = ON;
            }
        }
        
        else{
            buzzerPin.output();                                     
            buzzerPin = LOW; 
            uartUsb.write("Ignition Inhibited.\r\n", 21);
            if(!driverSeat){
                uartUsb.write("Driver seat not occupied.\r\n", 27);
            }
            if(!passengerSeat){
                uartUsb.write("Passenger seat not occupied.\r\n", 30);
            }
            if(!driverSeatBelt){
                uartUsb.write("Driver seatbelt not fastened.\r\n", 31);
            }
            if(!passengerSeatBelt){
                uartUsb.write("Passenger seatbelt not fastened.\r\n", 34);
            }
            
        }
        done = ON;
    }

}