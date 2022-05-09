#pragma once
#include "mbed.h"
#define HEADER_SIZE 2
#define FOOTER_SIZE 2

template<class dataType>
class Sender{
    public:
    Sender(PinName, PinName);
    BufferedSerial serial;
    dataType* original;
    char* originalChar;
    void send();
    void read();
    void readThread();
    char *buffer;
    char ch;
    int state;
    int i;
    Thread thread;
    bool isRecevied;
    dataType* replica;
    char header[2];
    char footer[2];
};

template<class dataType>
Sender<dataType>::Sender(PinName TX, PinName RX):serial(TX, RX, 57600){
    original = new dataType;
    originalChar = static_cast<char*>(static_cast<void*>(original));
    buffer = new char[sizeof(dataType)];
    static char const headerData[] = {6, 2};
    static char const footerData[] = {6, 3};
    strcpy(header, headerData);
    strcpy(footer, footerData);
    ch = 0;
    state = 0;
    i = 0;
    replica = new dataType;
    thread.start(callback(this, &Sender::readThread));
}
template<class dataType>
void Sender<dataType>::readThread(){
    while(true){
        read();
        ThisThread::sleep_for(2ms);
    }
}
template<class dataType>
void Sender<dataType>::send(){
        if(serial.writable()){
            serial.write(header, sizeof(header));
            serial.write(originalChar, sizeof(dataType));
            serial.write(footer, sizeof(footer));
        }
}
template<class dataType>
void Sender<dataType>::read(){
    if (serial.readable()) {
            serial.read(&ch, 1);
        switch (state) {
            case 0:
            if (ch == 6) {
                state++;
            }
            break;
            case 1:
            if (ch == 2) {
                state++;
                i = 0;
            }else if (ch == 6) {
            }else {
                state = 0;
            }
            break;
            case 2:
            buffer[i++] = ch;
            if (i >= sizeof(dataType)) {
                state++;
            }
            break;
            case 3:
            if (ch == 6) {
                state++;
            }
            break;
            case 4:
            if (ch == 3) {
                state = 0;
                replica = static_cast<dataType*>(static_cast<void*>(buffer));
                isRecevied = true;
                //printf("%d\r\n", replica->r2);
            }
            break;
        }
    }
}