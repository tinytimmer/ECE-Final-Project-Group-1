//need this to control the motor, which uses the PWM files to control it my bad yall

//PLEASE NOTE, This was used with the fan motor for lab 4 and will require adjustment. 

#include "motor.h"
#include <Arduino.h>

void motorSetup() {
  // Set all the motor control pins to outputs pin 11 & 10 on board
    DDRB |= (1 << DDB5) | (1 << DDB4);
    //DDRH |= (1 << DDH6); use this is we wanted to have another motor
}

void setDirection(int direction) {

  if (direction == 1) {
    PORTB |= (1 << DDB5);
    PORTB &= ~(1 << DDB4);
  }

  else {
    PORTB |= (1 << DDB4);
    PORTB &= ~(1 << DDB5);
  }

}
