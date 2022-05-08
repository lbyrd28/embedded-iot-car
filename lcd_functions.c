//------------------------------------------------------------------------------
//  Filename: lcd_functions.c
//
//  Description: This file contains the Main Routine - "While" Operating System
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

//Fuction Prototypes
void clearDisplay(void);

//==============================================================================
//==============================================================================

void clearDisplay(void) {
  strcpy(display_line[FIRST_LINE], "          ");
  strcpy(display_line[SECOND_LINE], "          ");
  strcpy(display_line[THIRD_LINE], "          ");
  strcpy(display_line[FOURTH_LINE], "          ");
}
