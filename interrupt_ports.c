//------------------------------------------------------------------------------
//  Filename: interrupt_ports.c
//
//  Description: This file contains the interrupts for ports
//
//
//  Logan Byrd
//  Oct 2019
//  Built with IAR Embedded Workbench Version: V7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

//Global Variables
extern volatile unsigned int sw1Pressed;
extern volatile unsigned int sw2Pressed;
extern volatile unsigned int debounce_needed1;
extern volatile unsigned int debounce_needed2;
extern volatile unsigned int switch1DebounceCounter;
extern volatile unsigned int switch2DebounceCounter;
extern volatile unsigned int okayToBlink;
extern char display_line[LCD_LINES][DISPLAYLENGTH];

//HW8
extern volatile char goSW1 = RESET_STATE;
extern volatile char goSW2 = RESET_STATE;

#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  // Switch 1
  if (P4IFG & SW1) {
    P4IFG &= ~SW1; // IFG SW1 cleared
    P4IE &= ~SW1;              //Disable SW1 interrupt
    sw1Pressed = TRUE;
    debounce_needed1 = TRUE;
    switch1DebounceCounter = RESET_STATE;
    goSW1 = TRUE;
    
    TB0CCTL1 |= CCIE;           //enable CCR1 interrupt
    
  }
}
#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  // Switch 2
  if (P2IFG & SW2) {
    P2IFG &= ~SW2; // IFG SW2 cleared
    P2IE &= ~SW2;              //Disable SW2 interrupt
    sw2Pressed = TRUE;
    debounce_needed2 = TRUE;
    switch2DebounceCounter = RESET_STATE;
    goSW2 = TRUE;
    
    TB0CCTL1 |= CCIE;           //enable CCR1 interrupt
  }
}