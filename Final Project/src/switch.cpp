#include "switch.h"
#include <avr/io.h>

//I started this but I havent worked on finishing this, would appreacite yallsa help on this -CT

/*
 * Initializes pull-up resistor on PE0 and sets it into input mode
 */
void initSwitchPE0(){

    // Initialize PE0 (pin 0) for input (set DDR to input). Enable pullup resistor.
    // NOTE: To set the port to input, we must 'clear' the bit by setting it to zero
    // while simultaneously preserving the other bits in the DDR register.

    DDRE &= ~( 1 << DDE0);  // Clear the bit in DDRD0
    PORTE |= (1 << PORTE0); // Enable pullup resistor by writing 1 to the port.

    // Pin-Change Interrupts must be enabled for pin PD0
    // We basically want to use INT0 as a pin change interrupt
    EICRA |= (1 << ISC00); EICRA &= ~(1 << ISC01); // Set INT0 to trigger asynchronously on any edge (high or low)

    EIMSK |= (1 << INT0);   // Enable INT0 in the EIMSK register
}