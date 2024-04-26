// Author:          Cole Rogers
// Net ID:         CRogers31
// Date:           3/14/2024
// Assignment:     Lab 3
// Description: initializes and controls the LCD display in any way necessary --writing strings, chars, instuctions. 
//----------------------------------------------------------------------//

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

void initLCD();
void fourBitCommandWithDelay(unsigned char data, unsigned int delay);
void eightBitCommandWithDelay(unsigned char command, unsigned int delay);
void writeCharacter(unsigned char character);
void writeString(const char *string);
void moveCursor(unsigned char x, unsigned char y);
void setCGRAM(unsigned char x);
void initLCDPins();
void initLCDProcedure();

//new: used to call the menu after selecting stuff and the operation is finished -CT
void LCDmenu();

#endif
