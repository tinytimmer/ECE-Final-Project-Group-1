#include <Arduino.h>
#include <avr/io.h>
#include "motor.h"
  //had to change the pins becuase these were occupied on my board for the LCD screen
  //from Davids note to me about the setup
  /* Using the DC motor (the fan) and the H-bridge (aka L293D chip)

  Arduino Pin 8 goes to H-Bridge Pin 1.
  Arduino Pin 7 goes to H-Bridge Pin 2.
  Arduino Pin 6 goes to H-Bridge Pin 7.
  Arduino 5V goes to rail, then to H-Bridge Pin 8.
  Ground goes to H-Bridge Pin 4.
  And the 5V also goes to H-Bridge Pin 16.
  The motor goes to H-Bridge pins 3 and 6. Doesn't matter which. Flipping them just reverses the direction.

    Changed it accoriding to my setup, I hope that is ok -CT
  */
  byte enablePin = 8;
  byte in1Pin = 7;
  byte in2Pin = 6;

void initMotor() {  
    // Pin Setup
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(enablePin, OUTPUT);
}

void setMotor(int speed, bool direction) {
    analogWrite(enablePin, speed);
    digitalWrite(in1Pin, !direction);
    digitalWrite(in2Pin, direction);
}
