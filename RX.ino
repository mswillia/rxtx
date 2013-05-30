#include <Servo.h>

const int channels = 6;

int led = 13;

//My trainer port output non-inverted logic signals, this may differ.
const int level = HIGH;

struct RC_Channel {
  unsigned int channel[channels];
};

struct RC_Channel rc;
struct RC_Channel defaults;

Servo channel[channels];

void setup() {

  //Set up each servo. Currently attached to d2-d8
  for (int i = 0; i < channels; ++i) {
    channel[i].attach(i+2);
  }
  
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
  //Our wireless serial device is setup to 57.6k baud
  Serial.begin(57600);
  
  //Default throttle
  defaults.channel[0] = 500;
  
  //Default others
  for (int i = 1; i < channels; ++i) {
    defaults.channel[i] = 1500;
  }
  
  for (int i = 0; i < channels; ++i) {
    rc.channel[i] = defaults.channel[i];
  }
}

//Wait for the buffer to fill to the specified number of bytes and return the first byte in the buffer
byte blockingRead(unsigned int wait) {
  while (Serial.available() < wait);
  return Serial.read();
}

void loop() {
  boolean found_frame = false;
  
  //Look for the start of a data frame
  if (Serial.read() == 0x00) {
      
    //Check that this really is the start of a data frame
    if (blockingRead(1) == 0x00) {
      found_frame = true;
      
      //Get the number of channels being transmitted
      //Note: This is mainly for future use so we won't have to statically set the number of channels
      int count = blockingRead(1);
      
     //Read data for each channel
      for (int i = 0; i < count; ++i) {
        int value = blockingRead(2);
            value |= Serial.read() << 8;
            
            //Store the value for writing
            rc.channel[i] = value;
      }
    }
  }
  
  //We did not find a data frame, go to a safe mode.
  if (!found_frame) {
     for (int i = 0; i < channels; ++i) {
      rc.channel[i] = defaults.channel[i];
    }
  }
  
  //Write values out to servos
  for (int i = 0; i < channels; ++i) {
      channel[i].writeMicroseconds(rc.channel[i]);
  }

}