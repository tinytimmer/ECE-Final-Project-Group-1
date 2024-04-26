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
// we will have to include a button for this that overrides the time to dispense
enum stateEnum {wait_press, debounce_press, wait_release, debounce_release};
volatile stateEnum state = wait_press; //Initialize the state to waiting for button press


/*  KEYPAD INITIALIZATION */
char keys[4][4] = { 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//The pins on the arduino board to connect your keypad to. 
//with the leftmost input, with the ribbon facing down and keypad up, being in pin 28. Changed this cuz since LCD was in those ports on my end and this was eaier to change than the LCD stuff 
// I hope that is ok -CT
byte rowPins[4] = {28,29,30,31}; //connect to the row pinouts of the keypad
byte colPins[4] = {32,33,34,35}; //connect to the column pinouts of the keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );

// Motor Setup
enum direction { OPEN_DOOR = true, CLOSE_DOOR = false};

//menu setup
/* void LCDmenu(){
  moveCursor(0, 0); // moves the cursor to 0,5 position
  writeString("Select Dog Size:");
  moveCursor(1, 0); // moves the cursor to 0,0 position
  writeString("1:S  2:M  3:L"); //write bottom line of LCD 
} */

/* DEFINITIONS */
//Delays to leave door open. 
#define SMALL_DELAY 1
#define MED_DELAY 1.5
#define LARGE_DELAY 2

//Delay to open/close door. 
#define DOOR_DELAY 2000


int main()
{
  init(); //initialize the keypad. MUST BE AT THE BEGINNING OF MAIN!
  Serial.begin(9600);
  sei();            // enable global interrupts

  initLCD();        //initializes LCD screen. using pins 22, 23, 24, 25... 7, 10, 12
  initSwitchPE0();  // TODO! IS THIS EVEN USED?
  initMotor();      //initializes the motor, using pins 5, 6, and 8.
  initTimer1();     // initializes timer1. USdelay. 
  initTimer2();     // initializes timer2. MSdelay.
  initTimer3();     // initializes timer3. delayMin. 

  LCDmenu();        // opens the default LCD menu screen. 
  

  while (1)
  {
    /* moveCursor(0, 0); // moves the cursor to 0,5 position
    writeString("Select Dog Size:");
    moveCursor(1, 0); // moves the cursor to 0,0 position
    writeString("1:S  2:M  3:L"); //write bottom line of LCD */

    //use keypad to select size of dog and print to screen
    char key = kpd.getKey();
    if (key) {
      if ((key == '1') | (key == '2') | (key == '3')) {
          int chosenDelay = 0; //to be set based on selection of animal size. 

          //LCD screen initialization
          moveCursor(0,0);
          writeString("                ");
          moveCursor(1,0);
          writeString("                ");
          moveCursor(0,0);

        if(key == '1') {
            //Write selection
            writeString("Small dog");

            //chosen delay.
            chosenDelay = SMALL_DELAY;
        } else if (key == '2') {
          //Write selection
          writeString("Medium dog");

          //chosen delay.
          chosenDelay = MED_DELAY;
        } else if (key == '3') {
          //Write selection
          writeString("Large dog");

          //chosen delay.
          chosenDelay = LARGE_DELAY;
        }

        //motor portion
        //How this works is after selecting the dog size it goes through this motor portion dispense the food based on the time associated with the size
        //  after this is done it goes back to the main menu letting the user select another dog size.
        //  I didnt implement a scrict time for this like normal everyday dog feeders, but we def can include this if yall want to. 
        //  Once its done dispensing the food it will make a smiley face on the 8x8 LED matrix for x amount of time before return to a neutral face and the main menu 
        //  I hope this makes sense to yall. -CT
        setMotor(OPEN_DOOR);
        // Time it takes for door to open
        delayMs(DOOR_DELAY);
        // Stop motor
        stopMotor();
        // Time door remains open for food to pour into bowl, use the delay for minutes for the presentation, 1 minute to test it. This worked! -CT
        //_delay_ms(5000);
        delayMin(chosenDelay);
        // Close food door
        setMotor(CLOSE_DOOR);
        // Time it takes for door to close
        delayMs(DOOR_DELAY);
        // Stop motor
        stopMotor();
      
        //put the code for 8x8 LED matrix to display a smiley face once its done dispensing the food -CT

        //return to main menu
        delayMs(1000);
        LCDmenu(); 
      }
      else if (key == '#')
      {
        Serial.println(key);
        //LCD screen portion
        moveCursor(0,0);
        writeString("                ");
        moveCursor(1,0);
        writeString("                ");
        moveCursor(0,0);
        writeString("Thanks for");
        moveCursor(1,0);
        writeString("using this!");
        delayMs(1000);
        //doesnt go back to the menu (theoretically) -CT

        break;
      }
    }
    //work with David to open and close door accroding to input, blocked for now to make sure keypad and lcd work together, keeping this here in case something goes wrong with code above -CT
/*     direction = true;
    setMotor(speed, direction);
    // Time it takes for door to open
    _delay_ms(2000);

    // Stop motor
    setMotor(0, direction);

    // Time door remains open for food to pour into bowl
    _delay_ms(5000);

    // Close food door
    direction = false;
    setMotor(speed, direction);
    // Time it takes for door to close
    _delay_ms(2000);

    // Stop motor
    setMotor(0, direction);  
    
    
    */ 


/*     //scarpping this idea since the above works for now -CT
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
    } */

    

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
