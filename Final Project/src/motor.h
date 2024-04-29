// Description: Function prototypes for motor.cpp
//----------------------------------------------------------------------//

#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#include <avr/io.h>

void initMotor(); // initates the motor to pin 9 on mega2560

void openDoor(); // command to open the door, this is based on degrees

void closeDoor(); // command to close door, based on degrees

#endif
