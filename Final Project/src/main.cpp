// When you can see this in Github and can successfully edit it, please put your name and Net ID
//  Author: Carmen Timmer, Enoch Dew, Cole Rogers, David Stefek
//  Net ID: cvtimmer,
//  Date: 4/8/2024
//  Assignment:     Final Project
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

Input sensor. (ie 4x4 keypad)
    - Accept input from the user to be used in the system. (menu driven selection)
    - Accept override input form button at any time

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


//set of states that will be used in the state machine using enum
enum stateEnum {wait_press, debounce_press, wait_release, debounce_release};
volatile stateEnum state = wait_press; //Initialize the state to waiting for button press

/*  KEYPAD INITIALIZATION */
const byte ROWS = 4;
const byte COLS = 4; 
char keys[ROWS][COLS] = { 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//The pins on the arduino board to connect your keypad to. 
//with the leftmost input, with the ribbon facing down and keypad up, being in pin 22. 
byte rowPins[ROWS] = {22,23,24,25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26,27,28,29}; //connect to the column pinouts of the keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int main()
{
  init(); //initialization for the keypad. MUST BE AT THE BEGINNING OF MAIN!
  
  Serial.begin(9600);
  sei(); // enable global interrupts

  // initialize stuff here
  initTimer1();

  while (1)
  {
    //Simple Keypad reading
    char key = kpd.getKey();
    if (key) {
      Serial.println(key);
    }

    moveCursor(0, 5); // moves the cursor to 0,0 position
    writeString("Welcome!"); //write top line of LCD, we could also give this a funny name to display when it returns to this if we want to
    delayMs(10000);
    moveCursor(0, 0); // moves the cursor to 0,0 position
    writeString("Select Dog Size:"); //write bottom line of LCD
    moveCursor(0, 0); // moves the cursor to 0,0 position
    delayMs(1500);
    writeString("1: Small ");
    moveCursor(0, 9); // moves the cursor to 0,9 position
    writeString("2: Med "); 
    moveCursor(1, 0); // moves the cursor to 1,0 position
    writeString("3: Large ");
    //after selecting, these options should go away, will be done in the switch case below

    //switch for button press
    //we could use this to override the timing system and dispense the food when pressed, an idea that could make our project unique
    switch(state) {
      case wait_press:
        delayMs(1);
        break;
      case debounce_press:
        delayMs(1); //Adds delay to account for debounce period
        state = wait_release;
        break;
      case wait_release: 
      break;
      case debounce_release: //Add delay to account for debounce period
        delayMs(1);
        state = wait_press;
        break;
    }

    //use this as a menu which should work with the motor in dispensing the food and the timer for how long it needs to dispense and when (if applicable)
/*  switch(selection){
            
      case 1: //small dog


      case 2: //medium dog


      case 3: //large dog
                
    } */ 

  }
}

ISR(PCINT0_vect){
  if (state == wait_press){
    state = debounce_press;
  }
  else if (state == wait_release) {
    state = debounce_release;
  }
}
