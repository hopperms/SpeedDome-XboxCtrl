#include <XBOXONE.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXONE Xbox(&Usb);

// Define Pins
int DE = 2;

// Define variables for remembering current state
int PAN = 0;
int TILT = 0;
int FOCUS = 0;
int ZOOM = 0;
int IRIS = 0;

void setup() {
  Serial.begin(4800); //4800 when connected to RS-422
  pinMode(DE, OUTPUT); // DE pin set to output
  digitalWrite(DE, HIGH); // DE pin set to HIGH to enable TX
  if (Usb.Init() == -1) { // Wait until Xbox controller is connected
    while (1); //halt
  }
}
void loop() {
  Usb.Task();
  if (Xbox.XboxOneConnected) { 
      //*************************** Pan *************************************
      if (Xbox.getAnalogHat(LeftHatX) > 7500 && PAN == 0) { // Pan Right
        Serial.write(0x01); //Address
        Serial.write(0x81); //Command Code
        Serial.write(0x7E); //Checksum
        PAN = 1;
      }
      if (Xbox.getAnalogHat(LeftHatX) < -7500 && PAN == 0) { // Pan Left
        Serial.write(0x01); 
        Serial.write(0x82); 
        Serial.write(0x7D); 
        PAN = 1;
      }
      if (Xbox.getAnalogHat(LeftHatX) < 7500 && Xbox.getAnalogHat(LeftHatX) > -7500 && PAN == 1){ // Pan Stop
        Serial.write(0x01); 
        Serial.write(0x83); 
        Serial.write(0x7C); 
        PAN = 0;
      }
      
      //*************************** Tilt *************************************
      if (Xbox.getAnalogHat(LeftHatY) > 7500 && TILT == 0) { // Tilt Up
        Serial.write(0x01); 
        Serial.write(0x85); 
        Serial.write(0x7A); 
        TILT = 1;
      }
      if (Xbox.getAnalogHat(LeftHatY) < -7500 && TILT == 0) { // Tilt Down
        Serial.write(0x01); 
        Serial.write(0x84); 
        Serial.write(0x7B);
        TILT = 1;
      }
      if (Xbox.getAnalogHat(LeftHatY) < 7500 && Xbox.getAnalogHat(LeftHatY) > -7500 && TILT == 1){ // Tilt Stop
        Serial.write(0x01); 
        Serial.write(0x86); 
        Serial.write(0x79); 
        TILT = 0;
      }
      
      //*************************** Focus *************************************
      if (Xbox.getAnalogHat(RightHatY) > 7500 && FOCUS == 0) { // Focus Far
        Serial.write(0x01); 
        Serial.write(0x88); 
        Serial.write(0x77); 
        FOCUS = 1;
      }
      if (Xbox.getAnalogHat(RightHatY) < -7500 && FOCUS == 0) { // Focus Near
        Serial.write(0x01);
        Serial.write(0x87);
        Serial.write(0x78);
        FOCUS = 1;
      }
      if (Xbox.getAnalogHat(RightHatY) > -7500 && Xbox.getAnalogHat(RightHatY) < 7500 && FOCUS == 1){ // Focus Stop
        Serial.write(0x01);
        Serial.write(0x89);
        Serial.write(0x76);
        FOCUS = 0;
      }
      
      //*************************** Iris *************************************
      if (Xbox.getAnalogHat(RightHatX) > 7500 && IRIS == 0) { // Iris Open
        Serial.write(0x01); 
        Serial.write(0x90);
        Serial.write(0x6F);
        IRIS = 1;
      }
      if (Xbox.getAnalogHat(RightHatX) < -7500 && IRIS == 0) { // Iris Close
        Serial.write(0x01); 
        Serial.write(0x91); 
        Serial.write(0x6E); 
        IRIS = 1;
      }
      if (Xbox.getAnalogHat(RightHatX) > -7500 && Xbox.getAnalogHat(RightHatX) < 7500 && IRIS == 1){ // Iris Stop
        Serial.write(0x01);
        Serial.write(0x92);
        Serial.write(0x6D);
        IRIS = 0;
      }
      
      
      //*************************** Zoom *************************************
      if (Xbox.getButtonPress(R2) > 0 && ZOOM == 0){ // Zoom In
        Serial.write(0x01);
        Serial.write(0x8A);
        Serial.write(0x75);
        ZOOM = 1;
      }
      if (Xbox.getButtonPress(L2) > 0 && ZOOM == 0){ // Zoom Out
        Serial.write(0x01);
        Serial.write(0x8B);
        Serial.write(0x74);
        ZOOM = 1;
      }
      if (Xbox.getButtonPress(L2) == 0 && Xbox.getButtonPress(R2) == 0 && ZOOM == 1){ // Zoom Stop
        Serial.write(0x01);
        Serial.write(0x8C);
        Serial.write(0x73);
        ZOOM = 0;
      }
      
      //*************************** All Stop *************************************
      if (Xbox.getButtonClick(X)){
        Serial.write(0x01);
        Serial.write(0x93);
        Serial.write(0x6C);
        PAN = 0;
        TILT = 0;
        FOCUS = 0;
        IRIS = 0;
        ZOOM = 0;
      }        
  }
  delay(1);
}
