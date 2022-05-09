# Serial-send-Object
A mbed (or Arduino) program for transmitting data between 2 MCU.

The Master branch contains the mbed program for STM32F103RB.

The mbed-os version is 6.13.

Receiving function is done in a stand-alone thread in the class.

When you declare a Sender object, the thread starts receiving automatically.

You may call the send function in the main or other thread to send an object.

The object type is defined when you declare the Sender object.

If you define the Sender object with "int", the Sender object will contain an "int" in it called "original".

Same to any other data type or self-defined class.

When the send function is called, the "original" member var/obj will be sent so you may want to modify its value before sending it.

The "original" is a public pointer, you can change its value by using "->".
