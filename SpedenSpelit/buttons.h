#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile byte buttonPressed; // Pelilogiikkaa varten talteen mitä pinniä painettiin.
extern bool canPress; // Nappien debounce logiikka. Tätä muuttujaa käsitellään pelilogiikassa.
extern bool gameRunning; // Onko peli päällä.

/* 
  Laitetan pinnit 2-6 INPUT_PULLUP tilaan ja asetetaan rekisteristä interruptit pinneistä 2-6. 
*/
void initButtonsAndButtonInterrupts(void);

// Muokkaa muuttujan arvoa pinneistä 2-6 -> 1-5
int convert (int);

// Intoduce PCINT2_vect Interrupt SeRvice (ISR) function for Pin Change Interrupt.
ISR(PCINT2_vect); 
#endif;