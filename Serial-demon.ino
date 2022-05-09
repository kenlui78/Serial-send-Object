#include"remoteButton.h";
#include <arduino-timer.h>

HardwareSerial mySerial(1);

void setup() {
  mySerial.begin(57600, SERIAL_8N1, 5, 18);//rx = 5, tx = 18
  Serial.begin(115200);
}

void loop() {
  RemoteButton* original = new RemoteButton;
  original->r2 = 0;
  char* originalChar = static_cast<char*>(static_cast<void*>(original));
  //Create an char pointer and make it point to the object.
  char *buffer = new char[sizeof(RemoteButton)];
  char ch;
  int state = 0;
  int i = 0;
  char header[] = { 6, 2 };
  char footer[] = { 6, 3 };

  long int t1 = millis();

  Serial.println("Program start.");
    while (true) {
        if (millis() - t1 > 1000){
          mySerial.write(header, sizeof(header));
          mySerial.write(originalChar, sizeof(RemoteButton));
          mySerial.write(footer, sizeof(footer));
          original->r2++;
          t1 = millis();
          //Serial.println(millis());
        }
        if (mySerial.available() > 0) {
            mySerial.read(&ch, 1);
        switch (state) {
            case 0:
            if (ch == 6) {
                state++;
            }
            break;
            case 1:
            if (ch == 2) {
                state++;
                //Serial.printf("head\r\n");
                i = 0;
            }else if (ch == 6) {
            }else {
                state = 0;
            }
            break;
            case 2:
            buffer[i++] = ch;
            if (i >= sizeof(RemoteButton)) {
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
                RemoteButton* replica = static_cast<RemoteButton*>(static_cast<void*>(buffer));
                Serial.printf("r2: %d\r\n", replica->r2);
            }
            break;
        }
        }
        delay(2);
    }


}
