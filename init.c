//------------------------------------------------------------------------------
//  Filename: init.c
//
//  Description: This file contains initialization for the LCD Screen text.
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


  // Global Variables
extern char display_line[LCD_LINES][DISPLAYLENGTH];
extern char *display[LCD_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;

// Function Prototypes
void Init_Conditions(void);
void Init_Ports(void);                   
void Init_Clocks(void);                    
void Init_Timers(void);        
void Init_LCD(void);                
void clearDisplay(void);                   
void Init_ADC(void);       
void Init_Serial(void);           
void delayFor100ms (int hundreds_ms);
void Init_LEDs(void);
void Init_Main(void);

//===========================================================================================
//===========================================================================================

void Init_Main(void){

  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();
  Init_Timers();                       // Initialize Timers
  Init_LEDs();
  Init_ADC();                          // Initialize the ADC
  Init_Serial();                       // Initialize serial communication
  P5OUT &= ~IOT_RESET;                  // Reset IOT
  delayFor100ms(PASSED_200MS);         // Wait 200ms before setting IOT reset high [needs 100ms minimum]
  P5OUT |= IOT_RESET;                  // Set IOT reset high to complete reset
  Init_LCD();                          // Initialize LCD

//===============================================================
//      Initial LCD Screen
//===============================================================  
  strcpy(display_line[FIRST_LINE], "          ");
  update_string(display_line[FIRST_LINE], RESET_STATE);
  strcpy(display_line[SECOND_LINE], "          ");
  update_string(display_line[SECOND_LINE], TRUE);
  strcpy(display_line[THIRD_LINE], "          ");
  update_string(display_line[FOURTH_LINE], FOURTH_LINE);
  enable_display_update();
  Display_Update(THREE_LINES,TRUE,RESET_STATE,RESET_STATE);
//------------------------------------------------------------------------------
}

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=BEGIN;i<DISPLAYLENGTH;i++){
    display_line[FIRST_LINE][i] = RESET_STATE;
    display_line[SECOND_LINE][i] = RESET_STATE;
    display_line[THIRD_LINE][i] = RESET_STATE;
    display_line[FOURTH_LINE][i] = RESET_STATE;
  }
  display_line[FIRST_LINE][END_LINE] = RESET_STATE;
  display_line[SECOND_LINE][END_LINE] = RESET_STATE;
  display_line[THIRD_LINE][END_LINE] = RESET_STATE;
  display_line[FOURTH_LINE][END_LINE] = RESET_STATE;

  display[FIRST_LINE] = &display_line[FIRST_LINE][BEGIN_LINE];
  display[SECOND_LINE] = &display_line[SECOND_LINE][BEGIN_LINE];
  display[THIRD_LINE] = &display_line[THIRD_LINE][BEGIN_LINE];
  display[FOURTH_LINE] = &display_line[FOURTH_LINE][BEGIN_LINE];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
}