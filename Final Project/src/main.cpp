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
#include "switch.h"


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
byte rowPins[ROWS] = {28,29,30,31}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {32,33,34,35}; //connect to the column pinouts of the keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int main()
{
  init(); //initialize the keypad. MUST BE AT THE BEGINNING OF MAIN!

  Serial.begin(9600);
  sei(); // enable global interrupts
  initLCD();
  initSwitchPE0();
  //initTimer0(); //LCD and keypad freak out when this is used, otherwise its functions correctly
  initTimer1();

  while (1)
  {
    
    moveCursor(0, 0); // moves the cursor to 0,5 position
    writeString("Select Dog Size:");
    moveCursor(1, 0); // moves the cursor to 0,0 position
    writeString("1:S  2:M  3:L"); //write bottom line of LCD
    
    char key = kpd.getKey();
      if (key) {
        Serial.println(key);
      }
  
    //switch for button press
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
      //Serial.println("button release");
        delayMs(1);
        state = wait_press;
        break;
    }

    //use keypad to select size of dog and print to screen

  }
}


ISR(INT0_vect){
  //Serial.println("switch has been HIT");
  if (state == wait_press){
    state = debounce_press;
  }
  else if (state == wait_release) {
    state = debounce_release;
  }
}
