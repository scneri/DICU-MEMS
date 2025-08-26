#include <SoftwareSerial.h>
#include <Arduino.h>

SoftwareSerial bluetooth(10, 11); // RX, TX para HC-05
SoftwareSerial mySerial(3, 2);    // RX, TX para RS232

void setup() {
pinMode(9, OUTPUT);     
digitalWrite(9, HIGH);  
mySerial.begin(9600);
Serial.begin(9600);     
bluetooth.begin(9600);  

Serial.println("Miau");
}

void loop() {
// Si hay datos desde Bluetooth, envíalos a RS232
if (bluetooth.available()) {
char c = bluetooth.read();
mySerial.write(c);
Serial.print("BT->RS232: ");
Serial.println(c);
}

// Si hay datos desde RS232, envíalos a Bluetooth
if (mySerial.available()) {
char c = mySerial.read();
bluetooth.write(c);
Serial.print("RS232->BT: ");
Serial.println(c);
}
}