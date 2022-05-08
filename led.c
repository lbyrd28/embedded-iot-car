//------------------------------------------------------------------------------
//  Filename: led.c
//
//  Description: This file contains the initialization of the LEDs.
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



void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  GREEN_LED_OFF;
  RED_LED_OFF;
//------------------------------------------------------------------------------
}

