#include <Arduino.h>
#include <avr/io.h>
#include "motor.h"

  byte enablePin = 11;
  byte in1Pin = 10;
  byte in2Pin = 9;

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
