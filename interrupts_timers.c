//------------------------------------------------------------------------------
//  Filename: interrupts_timers.c
//
//  Description: This file contains the interrupts associataed with the timers.
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
extern volatile unsigned char tB0CCR0Counter = RESET_STATE;
extern volatile unsigned int sw1Pressed = RESET_STATE;
extern volatile unsigned int sw2Pressed = RESET_STATE;
extern volatile unsigned int debounce_needed1 = RESET_STATE;
extern volatile unsigned int debounce_needed2 = RESET_STATE;
extern volatile unsigned int switch1DebounceCounter = RESET_STATE;
extern volatile unsigned int switch2DebounceCounter = RESET_STATE;
extern volatile char startMoving = RESET_STATE;
extern volatile char calibrateDone = RESET_STATE;
volatile char CCR2_Timer = RESET_STATE;
extern volatile char oneSecPassed = RESET_STATE;
extern volatile char overLineTime;
volatile char displaytimer = RESET_STATE;
extern volatile unsigned char update_display;
extern volatile unsigned int dTime = RESET_STATE;
extern volatile unsigned char lapTimeDecimal = RESET_STATE;
extern volatile unsigned char display_changed;
extern volatile unsigned int displayTime = RESET_STATE;
extern volatile char displayFirstTime = TRUE;
char countTime = RESET_STATE;
extern volatile char everySecond = RESET_STATE;

//------------------------------------------------------------------------------
// CCR Intervals
// CCR0 = 100 ms [contains LCD reset]
// CCR1 = 100 ms [FOR SWITCH DEBOUNCE!!!!!!!!!!]
// CCR2 = 50 ms
//==============================================================================
//==============================================================================


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerB0 0 Interrupt handler (for CCR0)
  //----------------------------------------------------------------------------
  tB0CCR0Counter++;             //Increment CCR0 counter (increments every 100ms)
  if(++displaytimer == PASSED_200MS){ //For LCD reset
    update_display = TRUE;
    display_changed = TRUE;
    displaytimer = RESET_STATE;
  }
  if(++countTime == PASSED_1S){
    countTime = RESET_STATE;
    everySecond = ~everySecond;
        if(!displayFirstTime){
        displayTime++;
      }
  }
  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
  //----------------------------------------------------------------------------
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler (for CCR1-overflow)
  //----------------------------------------------------------------------------
  switch(__even_in_range(TB0IV,GO_THRU_CCR)){
  case NO_INTERRUPT: break; // No interrupt
  case CCR1: // CCR1 used for debounce
    //Button 1 case=================================================================
    if(debounce_needed1) {
      if(switch1DebounceCounter++ >= SWITCH1_DEBOUNCE_TIME){
        P4IE |= SW1;              //Enable SW1 interrupt
        //startMoving = TRUE;       //Start the wheels
        sw1Pressed = FALSE;       //No more valid button
        debounce_needed1 = FALSE; //Debounce finished
      }
    }
    //Button 2 case=================================================================
    else if(debounce_needed2) {
      if(switch2DebounceCounter++ >= SWITCH2_DEBOUNCE_TIME){
        P2IE |= SW2;              //Enable SW2 interrupt
        sw2Pressed = FALSE;       //No more valid button
        //calibrateDone++;
        debounce_needed2 = FALSE; //Debounce finished
      }    
    }
    //No Buttons case===============================================================
    else {
      TB0CCTL1 &= ~CCIE;  //disable the interrupt
    }
    TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
    break;
  case CCR2: // CCR2 used for interrupt timer (variable controlled)
    //50ms timer
    overLineTime++;
    //1 second timer
    if(CCR2_Timer++ == ONE_SEC_CCR2) {
      //Set variable needed to pass here:
      oneSecPassed = TRUE;
      CCR2_Timer = RESET_STATE;
      overLineTime = RESET_STATE;
      TB0CCTL2 &= ~CCIE;  //disable the interrupt 
    }
    break;
  case OVERFLOW: // overflow
    break;
  default: break;
  }
  //----------------------------------------------------------------------------
}