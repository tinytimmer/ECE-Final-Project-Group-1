// Description: Function prototypes for motor.cpp
//----------------------------------------------------------------------//

#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#include <avr/io.h>

void initMotor();

void setMotor(int speed, bool direction);

#endif
