#include "mbed.h"
#include "remoteButton.h"
#include "Sender.h"
#include <cstdint>
#include <cstdio>
//F103RB serial pin config
#define UART1_TX PA_9   
#define UART1_RX PA_10
#define UART3_TX PB_10
#define UART3_RX PB_11
BufferedSerial pc(USBTX, USBRX, 115200);
//F446RE serial pin config

int main()
{
    Sender<RemoteButton> sender(UART1_TX, UART1_RX);
	sender.original->r2 = 0;
    Timer timer;
    timer.start();
    pc.write("Program start.\r\n", 18);
    while (true) {
        if(timer.elapsed_time() > 1s){
            sender.original->r2++;
            sender.send();
            timer.reset();
        }
        if (sender.isRecevied) {
            sender.isRecevied = false;
            printf("r2: %d\r\n", sender.replica->r2);
        }
        ThisThread::sleep_for(2ms);
    }
}
