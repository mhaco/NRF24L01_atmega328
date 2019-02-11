/* -----------------------------------------------------------------------------
 - Request
   - FR24 library
 - Connections
   - nRF24L01 to Arduino
     1 GND      GND
     2 VCC   3V3
     3 CE  D9
     4 CSN   D10
     5 SCK   D13
     6 MOSI  D11
     7 MISO  D12
     8 UNUSED 
* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/* Ports ---------------------------------------------------------------------*/
#define CE_PIN   7
#define CSN_PIN 8
/* nRF24l01 ------------------------------------------------------------------*/
// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/* Joystick ------------------------------------------------------------------*/
int value[2]; // 1 element array holding value readings
/* ---------------------------------------------------------------------------*/

/*
 - setup function
 * ---------------------------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
  delay(1000);
  
  radio.begin();
  radio.setRetries(0, 15);//Set the number and delay of retries upon failed submit.
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(pipe);
  value[0] = 20000;
  value[1] = 1;
}

/*
 - loop function
 * ---------------------------------------------------------------------------*/
void loop()
{
  Serial.print("sal");Serial.println(value[1]);
  radio.write( value, sizeof(value) );
  delay(1);
}
