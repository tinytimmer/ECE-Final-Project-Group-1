#include <Arduino.h>
#include <avr/io.h>
#include "motor.h"
#include "timer.h"
#include <Servo.h>

Servo myservo;

void initMotor()
{
  myservo.attach(9); // attachs the servo on pin 9 to servo object
  myservo.write(0);  // back to 0 degrees
  delay(1000);       // wait for a second
}

void openDoor()
{
  for (int i = 0; i <= 180; i++)
  {
    myservo.write(i); // write the i angle to the servo
  }
}

void closeDoor()
{
  for (int i = 180; i >= 0; i--)
  {
    myservo.write(i); // write the i angle to the servo
  }
}

/* int input_key; // used to tell next function what input was checked and dispenses the food accordingly
int dispenseFood(input_key)
{
  if (input_key)
  {
    if (input_key == 1)
    {
      // SMALL DOG
      unsigned int delayMin(1);
      // Open food door
      void openDoor();
      // Time door remains open for food to pour into bowl SMALL DOG
      unsigned int delayMs(1500);
      // Close food door
      void closeDoor();
    }
    else if (input_key == 2)
    {
      // MED_DOG
      unsigned int delayMin(1);
      // Open food door
      void openDoor();
      // Time door remains open for food to pour into bowl SMALL DOG
      unsigned int delayMs(2000);
      // Close food door
      void closeDoor();
    }
    else if (input_key == 3)
    {
      // LAGRE_DOG
      unsigned int delayMin(1);
      // Open food door
      void openDoor();
      // Time door remains open for food to pour into bowl SMALL DOG
      unsigned int delayMs(2500);
      // Close food door
      void closeDoor();
    }
  }
} */