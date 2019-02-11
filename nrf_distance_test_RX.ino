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
/* Value ------------------------------------------------------------------*/
int value[2]; // 1 element array holding Joystick readings
/* ---------------------------------------------------------------------------*/

/*
 - setup function
 * ---------------------------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("nRF24l01 Receiver Starting");
  radio.begin();
  radio.setRetries(0, 15);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(2, OUTPUT);
}

/*
 - loop function
 * ---------------------------------------------------------------------------*/
void loop()
{
  if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done)
    {
      // Fetch the data payload
      done = radio.read( value, sizeof(value) );
      Serial.print("Value 1 :");Serial.println(value[0]);
      Serial.print("Value 2 :");Serial.println(value[1]);
      if (value[0] != 0){
        digitalWrite(5, HIGH);
      }
      else{
        digitalWrite(5, LOW);
      }
    }
  }
  else
  {    
    Serial.println("No radio available");
    digitalWrite(2, LOW);
  }
}
