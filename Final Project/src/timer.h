#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer0();
void delayMs(unsigned int delay);
void initTimer1();
void delayUs(unsigned int delay);
void initTimer3();
void delayMin(unsigned int delay);

#endif