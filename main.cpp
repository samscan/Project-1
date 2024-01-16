#include "mbed.h"
#include "arm_book_lib.h"

DigitalIn driverSeat(D2);
DigitalIn driverSeatBelt(D3);
DigitalIn passengerSeat(D4);
DigitalIn passengerSeatBelt(D5);
DigitalIn ignition(D6);
DigitalOut ignitionEnabled(LED1);
DigitalOut engineStarted(LED1);
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

bool driverSeatState = OFF;

void inputsInit();
void outputsInit();
void updateDriverSitting();
//void updateReadyToDrive();
//void updateEngineStarted();

int main()
{
    inputsInit();
    outputsInit();

    while (true) {
        updateDriverSitting();
        //updateReadyToDrive();
        //updateEngineStarted();

        }
    
}

void inputsInit()
{
    driverSeat.mode(PullDown);
    driverSeatBelt.mode(PullDown);
    passengerSeat.mode(PullDown);
    passengerSeatBelt.mode(PullDown);
    ignition.mode(PullDown);
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