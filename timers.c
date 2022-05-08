//------------------------------------------------------------------------------
//  Filename: timers.c
//
//  Description: This file contains all the functions to create timers.
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

//Global variables
extern volatile unsigned int dTime;
extern volatile unsigned char tB0CCR0Counter;
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern volatile unsigned int okayToBlink;
unsigned int h100MsPass = PASSED_100MS;
unsigned h200MsPass = PASSED_200MS;
unsigned h1SPass = PASSED_1S;
extern char display_line[LCD_LINES][DISPLAYLENGTH];
extern unsigned char startLapTimer;
extern volatile unsigned char lapTimeDecimal;
extern volatile unsigned char lapTimeSeconds = RESET_STATE;
extern char adc_char[END1];
char firstTimeDisplay = TRUE;


//==============================================================================
// Main Timers Process (used in main loop)
//==============================================================================
//This function makes use of the CCR0 interrupt that occurs every 100ms
//to create a counter that can be used to make events recur in the main loop
void Timers(void) {
  //100ms
  if(tB0CCR0Counter == h100MsPass){
    h100MsPass += PASSED_100MS;
    dTime++;
  }
  
  //200ms
  if(tB0CCR0Counter == h200MsPass){
    h200MsPass+= PASSED_200MS;
    update_display = TRUE;
    display_changed = TRUE;
  }
  
  //1s
  if(tB0CCR0Counter >= h1SPass){
    tB0CCR0Counter = RESET_STATE;
    h100MsPass = PASSED_100MS;
    h200MsPass = PASSED_200MS;
  }
}


//==============================================================================
// Delay Function
//==============================================================================
//if hundreds_ms = 2 delay for 200ms, etc
void delayFor100ms (int hundreds_ms) { 
  dTime = RESET_STATE;
  while(dTime != hundreds_ms){
    Timers();
  }
}
 /*
   //Just use inside stuff if needed
void timerDelay (int fifty_ms){
  TB0CCTL2 |= CCIE;
  if(overLineTime = xxx){
    TB0CCTL2 &= ~CCIE;
    overLineTime = RESET_STATE;
    other stuff;
}
*/

//==============================================================================
// Initialization fucntions
//==============================================================================

//Main timer init called in main
void Init_Timers(void) {
  Init_Timer_B0();
  Init_Timer_B3();
}

//Initializaton of Timer B0
void Init_Timer_B0(void) {
  //***********************************************************************************************
  // Timer B0 features 6 different kinds of registers (total of 18):
  // TB0CTL : Timer_B0 Control
  // TB0CCTL0 thru TB0CCTL6 : Timer_B0 Capture/Compare Control Registers
  // TB0R : Timer_B0 Coutner
  // TB0CCR0 thru TB0CCR6 : Timer_B0 Capture/Compare Registers
  // TB0IV : Timer_B0 Interrupt Vector
  // TB0EX0 : Timer_B0 Expansion 0
  //---------------------------------------------------------------------------
  // TB0CTL Register : 
  //    Bit 15 is reserved
  //    Bit 14-13 is TBCLGRP ???
  //    Bits 12-11 are CNTL (counter length)
  //            00 = 16 bit (Max TB0R value is 0FFFFh)
  //            01 = 12 bit (Max TB0R value is 0FFFh)
  //            10 = 10 bit (Max TB0R value is 03FFh)
  //            11 = 8 bit (Max TB0R value is 0FFh)
  //    Bit 10 is reserved
  //    Bits 9-8 is TBSSEL (clock source select)
  //            00 = TB0CLK
  //            01 = ACLK
  //            10 = SMCLK
  //            11 = INCLK
  //    Bits 7-6 are ID (Input clk divider)
  //            00 = /1
  //            01 = /2
  //            10 = /4
  //            11 = /8
  //    Bits 5-4 are MC (Mode Control)
  //            00 = Stop Mode
  //            01 = Up Mode
  //            10 = Continous Mode
  //            11 = Up/down Mode
  //    Bit 3 is reserved
  //    Bit 2 is TBCLR (Setting this bit clears TB0R, the divider logic, and count direction)
  //    Bits 1 is TBIE (Timer_B Interrupt Enable)
  //            0 = Interrupt disabled
  //            1 = Interrupt enabled
  //    Bits 1 is TBIFG (Timer_B Interrupt Flag)
  //            0 = No interrupt pending
  //            1 = Interrupt pending 
  // TB0CCTLn Registers :
  //    Bits 15-14 is CM (Capture Mode)
  //            00 = No capture
  //            01 = Capture on rising edge
  //            10 = Capture on falling edge
  //            11 = Capture on both falling and rising edges
  //    Bits 13-12 is CCIS (Capture/Compare input select)
  //            00 = CCI0A
  //            01 = CCI0B
  //            10 = GND
  //            11 = VCC
  //    Bit 11 is SCS (Synchronize capture source)
  //            0 = Asynchronous capture
  //            1 = Synchronous capture
  //    Bit 10 is SCCI ???
  //    Bit 9 is reserved
  //    Bit 8 is CAP (Capture mode)
  //            0 = Compare mode
  //            1 = Capture mode
  //    Bits 7-5 is OUTMOD ???
  //    Bit 4 is CCIE (Capture/compare interrupt enable)
  //            0 = Interrupt disabled
  //            1 = Interrupt enabled
  //    Bit 3 is CCI (input signal read by this bit)
  //    Bit 2 is OUT (output)
  //            0 = Output low
  //            1 = Output high
  //    Bit 1 is COV (Capture overflow)
  //            0 = No capture overflow occured
  //            1 = Capture overflowed occrued
  //    Bit 0 is CCIGF (capture/compare interrupt flag)
  //            0 = No interrupt pending
  //            1 = Interrupt pending
  // TB0R Register :
  //    Bits 15-0 contain the Timer_B0 coutner value
  // TB0CCRn Registers :
  //    In compare mode: this register holds the data for the comparison to the
  //    timer value in the TB0R register
  //    In capture mode: the TB0R register is copied to the TB0CCRn register when
  //    a capture is performed
  // TABIV register:
  //    00h = No interrupt pending
  //    02h = Interrupt Source: Capture/compare 1; Interrupt Flag: TBxCCR1 CCIFG;
  //    Interrupt Priority: Highest
  //    04h = Interrupt Source: Capture/compare 2; Interrupt Flag: TBxCCR2 CCIFG
  //    06h = Interrupt Source: Capture/compare 3; Interrupt Flag: TBxCCR3 CCIFG
  //    08h = Interrupt Source: Capture/compare 4; Interrupt Flag: TBxCCR4 CCIFG
  //    0Ah = Interrupt Source: Capture/compare 5; Interrupt Flag: TBxCCR5 CCIFG
  //    0Ch = Interrupt Source: Capture/compare 6; Interrupt Flag: TBxCCR6 CCIFG
  //    0Eh = Interrupt Source: Timer overflow; Interrupt Flag: TBxCTL TBIFG; Interrupt
  //    Priority: Lowest
  // TB0EX0 Register:
  //    Bits 15-3 are reserved
  //    Bits 2-0 are TBIDEX (input divider expansion to divide clock further)
  //            000b = Divide by 1
  //            001b = Divide by 2
  //            010b = Divide by 3
  //            011b = Divide by 4
  //            100b = Divide by 5
  //            101b = Divide by 6
  //            110b = Divide by 7
  //            111b = Divide by 8
  //**********************************************************************************************.
  TB0CTL = TBSSEL__SMCLK; // SMCLK source
  TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  TB0CTL |= MC__CONTINOUS; // Continuous up
  // Divider==================================================
  TB0CTL |= ID_1; // Divide clock by 2
  TB0EX0 = TBIDEX_7; // Divide clock by an additional 8
  // CCR0 [Blinking LCD]=======================================
  TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
  TB0CCTL0 |= CCIE; // CCR0 enable interrupt
  // CCR1 [Switch Debounce]====================================
  TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
  TB0CCTL1 |= CCIE; // CCR1 enable interrupt
  // CCR2 [Timer Variables]====================================
  TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
  
  TB0CTL &= ~TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}

//Initialization of Timer B3 (for PWM)
void Init_Timer_B3(void) {
  //------------------------------------------------------------------------------
  // SMCLK source, up count mode, PWM Right Side
  // TB3.1 P6.0 R_FORWARD
  // TB3.2 P6.1 L_FORWARD
  // TB3.3 P6.2 R_REVERSE
  // TB3.4 P6.3 L_REVERSE
  //------------------------------------------------------------------------------
  TB3CTL = TBSSEL__SMCLK; // SMCLK
  TB3CTL |= MC__UP; // Up Mode
  TB3CTL |= TBCLR; // Clear TAR
  TB3CCR0 = WHEEL_PERIOD; // PWM Period
  TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM duty cycle
  TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM duty cycle
  TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
  TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM duty cycle
  //------------------------------------------------------------------------------
}

//==============================================================================
// Lap Timer
//==============================================================================

void lapTimer(void) {
  int i;
  switch(lapTimeDecimal){
  case FIRST:
    lapTimeDecimal = lapTimeDecimal++;
    HEXtoBCD(lapTimeDecimal);
    for(i=TIMER_BEGIN_CHAR; i<TIMER_END_CHAR; i++){
      display_line[FOURTH_LINE][i] = adc_char[i];
    }
    lapTimeDecimal--;
    break;
  case SECOND:
    lapTimeDecimal = lapTimeDecimal + DOWN_TWO;
    HEXtoBCD(lapTimeDecimal);
    for(i=TIMER_BEGIN_CHAR; i<TIMER_END_CHAR; i++){
      display_line[FOURTH_LINE][i] = adc_char[i];
    }
    lapTimeDecimal = lapTimeDecimal - DOWN_TWO;
    break;
  case THIRD:
    lapTimeDecimal = lapTimeDecimal + DOWN_THREE;
    HEXtoBCD(lapTimeDecimal);
    for(i=TIMER_BEGIN_CHAR; i<TIMER_END_CHAR; i++){
      display_line[FOURTH_LINE][i] = adc_char[i];
    }
    lapTimeDecimal = lapTimeDecimal - DOWN_THREE;
    break;
  case FOURTH:
    lapTimeDecimal = lapTimeDecimal + DOWN_FOUR;
    HEXtoBCD(lapTimeDecimal);
    for(i=TIMER_BEGIN_CHAR; i<TIMER_END_CHAR; i++){
      display_line[FOURTH_LINE][i] = adc_char[i];
    }
    lapTimeDecimal = lapTimeDecimal - DOWN_FOUR;
    break;
  default:
    HEXtoBCD(lapTimeDecimal);
    for(i=TIMER_BEGIN_CHAR; i<TIMER_END_CHAR; i++){
      display_line[FOURTH_LINE][i] = adc_char[i];
    }
    break;
  }
}