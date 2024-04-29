// When you can see this in Github and can successfully edit it, please put your name and Net ID
//  Author: Carmen Timmer,
//  Net ID: cvtimmer,
//  Date: 4/8/2024
//  Assignment:     Lab 5
//  if there is a file missing for this lab go ahead and add it in
//----------------------------------------------------------------------//

/*  SYSTEM REQUIREMENTS:
  1. Completely automated system
  2. Feeder cannot be accessed by pets.
  3. Measured ratios are dispensed based on size/type of animal.
  4. Ratios are correct based on the selection made from menu.

*/

/* TODO:

LCD Display:
    - Figure out communication protocol. Likely SPI. To communicate with the various devises.
    - Accept input to display text to user.
Stepper Motor:
    - Accept prompt to activate.
    - Activation will have the motor turn a designated amount (amount can be specified,
      but must be changeable for when physical model is ready.)
    - Can likely use the same system used in lab 4.
Input sensor.
    - Accept input from the user to be used in the system.
Timer system:
    -
    - Keeps track of long periods (up to 24 hours?)
    - Can be interrupted and reset.




*/

#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include "motor.h"
#include "lcd.h"
#include "Keypad.h"
#include "spi.h"

/*  KEYPAD INITIALIZATION */
char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
// The pins on the arduino board to connect your keypad to.
// with the leftmost input, with the ribbon facing down and keypad up, being in pin 28. Changed this cuz since LCD was in those ports on my end and this was eaier to change than the LCD stuff
//  I hope that is ok -CT
byte rowPins[4] = {28, 29, 30, 31}; // connect to the row pinouts of the keypad
byte colPins[4] = {32, 33, 34, 35}; // connect to the column pinouts of the keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

// Motor Setup w/ LCD and 8x8, needed to have the <Servo.h> library to work

int main()
{
  init(); // initialize the keypad. MUST BE AT THE BEGINNING OF MAIN!
  Serial.begin(9600);
  sei();             // enable global interrupts
  SPI_MASTER_Init(); // initializes SPI.
  initLCD();         // initializes LCD screen. using pins 22, 23, 24, 25... 7, 10, 12
  // initSwitchPE4(); // Will not be using this, use the pot to adjust the brightness of screen
  initMotor();  // initializes the motor, using pins 5, 6, and 8.
  initTimer1(); // initializes timer1. USdelay.
  initTimer2(); // initializes timer2. MSdelay.
  initTimer3(); // initializes timer3. delayMin.

  display_8x8(); // initializes 8x8 LED matrix display.
  write_dogFace();
  LCDmenu(); // opens the default LCD menu screen.

  while (1)
  {

    // use keypad to select size of dog and print to screen
    char key = kpd.getKey();
    if (key)
    {
      if ((key == '1') | (key == '2') | (key == '3') | (key == 'A') | (key == 'B') | (key == 'C'))
      {
        // LCD screen initialization
        moveCursor(0, 0);
        writeString("                ");
        moveCursor(1, 0);
        writeString("                ");
        moveCursor(0, 0);

        if (key == '1')
        {
          // Write selection
          write_smallDog(); // draw small dog on 8x8 matrix
          moveCursor(0, 0);
          writeString("Small dog"); // write this on LCD screen
          moveCursor(1, 0);
          writeString("Waiting to drop");
          delayMin(1); // one minute delay
          // Open food door
          openDoor();
          // Time door remains open for food to pour into bowl SMALL DOG
          delayMs(1500);
          // Close food door
          closeDoor();
          // tell user food has been dispensed using both the screen and 8x8 LED matrix
          write_arrowFlashing(5); // display flashing arrow # of times argument indicates on 8x8 LED matrix
          moveCursor(0, 0);
          writeString("                ");
          moveCursor(1, 0);
          writeString("                ");
          moveCursor(0, 0);
          moveCursor(0, 0);
          writeString("Food dispensed!");

          // return to main menu
          delayMs(1500);
          LCDmenu();
          write_dogFace();
        }
        else if (key == '2')
        {
          // Write selection
          write_medDog();
          writeString("Medium dog"); // write this on LCD screen
          moveCursor(1, 0);
          writeString("Waiting to drop");
          delayMin(1); // one minute delay
          // Open food door
          openDoor();
          // Time door remains open for food to pour into bowl SMALL DOG
          delayMs(1750);
          // Close food door
          closeDoor();
          // tell user food has been dispensed using both the screen and 8x8 LED matrix
          write_arrowFlashing(5); // display flashing arrow # of times argument indicates on 8x8 LED matrix
          moveCursor(0, 0);
          writeString("                ");
          moveCursor(1, 0);
          writeString("                ");
          moveCursor(0, 0);
          moveCursor(0, 0);
          writeString("Food dispensed!");

          // return to main menu
          delayMs(1500);
          LCDmenu();
          write_dogFace();
        }
        else if (key == '3')
        {
          // Write selection
          write_bigDog();
          writeString("Large dog"); // write this on LCD screen
          moveCursor(1, 0);
          writeString("Waiting to drop");
          delayMin(1); // one minute delay by default, can change this later if we figure out how to adjust this from the menu
          // Open food door
          openDoor();
          // Time door remains open for food to pour into bowl SMALL DOG
          delayMs(2000);
          // Close food door
          closeDoor();
          // tell user food has been dispensed using both the screen and 8x8 LED matrix
          write_arrowFlashing(5); // display flashing arrow # of times argument indicates on 8x8 LED matrix
          moveCursor(0, 0);
          writeString("                ");
          moveCursor(1, 0);
          writeString("                ");
          moveCursor(0, 0);
          moveCursor(0, 0);
          writeString("Food dispensed!");

          // return to main menu
          delayMs(1500);
          LCDmenu();
          write_dogFace();
        }
      }
      /*//this didnt work, it did register me pushing 'A' but it didnt return to the main menu
      else if (key == 'A')
      { // return to main menu
        delayMs(1500);
        LCDmenu();
        write_dogFace();
      }*/
      else if (key == '#')
      {
        Serial.println(key);
        // LCD screen portion
        moveCursor(0, 0);
        writeString("                ");
        moveCursor(1, 0);
        writeString("                ");
        moveCursor(0, 0);
        writeString("Thanks for using");
        moveCursor(1, 0);
        writeString("this device!");
        delayMs(1000);
        // finish using the device, doesnt go back to the menu UNLESS you press the rest button on the MCU

        // break; break will break out of the while loop entirely because this isn't a switch case
      }
    }
  }
}
/* tried to see if i could add this to give users a chace to select a time, didnt work
char key = kpd.getKey();
          if (key)
          {
            if ((key == 'A') | (key == 'B') | (key == 'C'))
            {
              if (key == 'A')
              {
                // SMALL DOG
                moveCursor(0, 0);
                writeString("1min selected");
                delayMin(0.5); // one minute delay
                // Open food door
                openDoor();
                // Time door remains open for food to pour into bowl SMALL DOG
                delayMs(1500);
                // Close food door
                closeDoor();
              }
              else if (key == 'B')
              {
                delayMin(0.5); // five minute delay
                // Open food door
                openDoor();
                // Time door remains open for food to pour into bowl SMALL DOG
                delayMs(1500);
                // Close food door
                closeDoor();
              }
              else if (key == 'C')
              {
                delayMin(0.5); // ten minute delay
                // Open food door
                openDoor();
                // Time door remains open for food to pour into bowl SMALL DOG
                delayMs(1500);
                // Close food door
                closeDoor();
              }
            }
          } */