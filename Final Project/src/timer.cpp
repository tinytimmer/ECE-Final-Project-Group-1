
#include "timer.h"
#include <avr/io.h>


/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    // set the time register to CTC
    TCCR0A &= ~(1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);
    // set the prescaller to clk/64
    TCCR0B |= (1 << CS00);
    TCCR0B |= (1 << CS01);
    TCCR0B &= ~(1 << CS02);
    // CTC compare value
    OCR0A = 250;
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
    TCNT0 = 0; //start the timer at 0
    TIFR0 |= (1 << OCF0A); // set compare flag to start timer

    for(unsigned int i = 0; i < delay; i++) {
        while(!(TIFR0 & (1 << OCF0A))) {} // wait until timer is flagged
        TIFR0 |= (1 << OCF0A); // restart timer
    }
}

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
    // set the time register to CTC
    TCCR1A &= ~(1 << WGM10);
    TCCR1A |= (1 << WGM11);
    TCCR1B &= ~(1 << WGM12);
    // set the prescaller to clk/1 (no prescaling)
    TCCR1B |= (1 << CS10);
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS12);
    // CTC compare value
    OCR1A = 16;
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    TCNT1 = 0; //start the timer at 0
    TIFR1 |= (1 << OCF1A); // set compare flag to start timer

    for(unsigned int i = 0; i < delay; i++) {
        while(!(TIFR1 & (1 << OCF1A))) {} // wait until timer is flagged
        TIFR1 |= (1 << OCF1A); // restart timer
    }
}

// Initialize timer 3 using CTC mode
void initTimer3(){
    // set the time register to CTC
    TCCR3A &= ~(1 << WGM30);
    TCCR3A |= (1 << WGM31);
    TCCR3B &= ~(1 << WGM32);
    // set the prescaller to clk/1024
    TCCR3B |= (1 << CS30);
    TCCR3B &= ~(1 << CS31);
    TCCR3B |= (1 << CS32);
    // CTC compare value
    OCR3A = 250; // The timer will flag every 16ms
}

// Delay the program for a specifified number of minutes
void delayMin(unsigned int delay){
    TCNT3 = 0; //start the timer at 0
    TIFR3 |= (1 << OCF3A); // set compare flag to start timer

    for(unsigned int i = 0; i < delay; i++) {
        for(unsigned int j = 0; j < 1875; j++) { // 16ms * 3750? = 60s to get 1 minute
            while(!(TIFR3 & (1 << OCF3A))) {} // wait until timer is flagged
            TIFR3 |= (1 << OCF3A); // restart timer 
        }
    }
}