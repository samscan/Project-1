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

void inputsInit();
void outputsInit();
void updateDriverSitting();
void updateReadyToDrive();
void updateEngineStarted();
void uartTask();

int main()
{
    inputsInit();
    outputsInit();

    while (true) {
        updateDriverSitting();

        }
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