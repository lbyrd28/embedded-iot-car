//------------------------------------------------------------------------------
//  Filename: wheels.c
//
//  Description: This file contains the state machine that the wheels will
//  run off of.
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
extern char display_line[LCD_LINES][DISPLAYLENGTH];
extern unsigned int next = FIRST;
extern volatile char startMoving; 
extern volatile char oneSecPassed;
extern volatile unsigned int ADC_LeftDetector;
extern volatile unsigned int ADC_RightDetector;
extern volatile char calibrateDone;
extern volatile unsigned int blackCalibrationHigh = RESET_STATE;
extern volatile unsigned int blackCalibrationLow = RESET_STATE;
extern volatile unsigned int whiteCalibrationHigh = RESET_STATE;
extern volatile unsigned int whiteCalibrationLow = RESET_STATE;
extern char beginDislplayingADC = RESET_STATE;
char firstClick = RESET_STATE;
extern volatile char overLineTime = RESET_STATE;
extern unsigned char startLapTimer = RESET_STATE;
int i;
extern char adc_char[END1];
extern volatile unsigned char lapTimeSeconds;

void wheelsProcess (void) {
  switch (next) {
  case FIRST:
    break;
  case SECOND: //travel to black line
    strcpy(display_line[FIRST_LINE], "BL Start  ");
    RIGHT_FORWARD_SPEED = FULL_SPEED;
    LEFT_FORWARD_SPEED = MAKEUP_SPEED;
    if(ADC_LeftDetector > BLACK || ADC_RightDetector > BLACK){
      next = THIRD;
    }
    break;
  case THIRD: //found line -stop
    fullStop();
    delayFor100ms(PASSED_2S);
    next = FOURTH;
    break;
  case FOURTH: //intercept
    strcpy(display_line[FIRST_LINE], "Intercept ");
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = MAKEUP_SPEED;
    delayFor100ms(PASSED_800MS);
      next = FIFTH;
    
    break;
  case FIFTH: //intercept
    strcpy(display_line[FIRST_LINE], "BL Circle ");
    if(ADC_RightDetector < BLACK) {
      RIGHT_FORWARD_SPEED = MAKEUP_SPEED2;
    LEFT_FORWARD_SPEED = HALF_SPEED;
    }
    else if (ADC_LeftDetector < BLACK) {
      RIGHT_FORWARD_SPEED = MAKEUP_SPEED2;
    LEFT_FORWARD_SPEED = HALF_SPEED;
    }
    else forwardTest();
    break;
  case SIXTH: //intercept
    strcpy(display_line[FIRST_LINE], "BL Exit   ");
    clockwise(FULL_SPEED);
    TB0CCTL2 |= CCIE;  //enable the 1-sec timer interrupt
    if(overLineTime == OVERLINETIME3){
      overLineTime = RESET_STATE;
      fullStop();
      next++;
      TB0CCTL2 &= ~CCIE;
    }
    break;
  case SEVENTH:
    RIGHT_FORWARD_SPEED = FULL_SPEED;
    LEFT_FORWARD_SPEED = FULL_SPEED;
    TB0CCTL2 |= CCIE;  //enable the 1-sec timer interrupt
    if(overLineTime == OVERLINETIME4){
      overLineTime = RESET_STATE;
      fullStop();
      next++;
    }
    break;
  case EIGHTH: //intercept
    strcpy(display_line[FIRST_LINE], "BL Stop   ");
    break;
  case TENTH:
    strcpy(display_line[FIRST_LINE], "BL Start  ");
    RIGHT_FORWARD_SPEED = FULL_SPEED;
    LEFT_FORWARD_SPEED = FULL_SPEED;
    delayFor100ms(PASSED_1S);
    next = SECOND;
  default: break;
  
  }
}
