//------------------------------------------------------------------------------
//  Filename: main.c
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


// Function Prototypes
void main(void);
void Init_Main(void);
void Display_Process(void);
void ADC_Display_Process(void);
void clearDisplay(void);
void Project09Process(void);


// Global Variables
extern char display_line[LCD_LINES][DISPLAYLENGTH];
extern char *display[LCD_LINES];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile char goSW1;
extern volatile unsigned int displayTime;
extern volatile char displayFirstTime;
extern char adc_char[END1];
extern volatile char everySecond;

//===========================================================================================
//===========================================================================================

void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //
  //------------------------------------------------------------------------------
  
  
  Init_Main();                   // Initialize Variables and Initial Conditions
  
  //Initial Screen
  strcpy(display_line[FIRST_LINE], " WAITING  ");
  strcpy(display_line[SECOND_LINE], "   FOR    ");
  strcpy(display_line[THIRD_LINE], "   INPUT  ");
  strcpy(display_line[FOURTH_LINE], "          ");
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    
    
    Display_Process();                 // Function for LCD screen
    Project09Process();
    if(goSW1){
      goSW1 = RESET_STATE;
      transmitStringUCA0("AT+RESET=1\r");
      delayFor100ms(PASSED_5S);
      transmitStringUCA0("AT+NSTCP=1024,1\r");
      delayFor100ms(PASSED_2S);
      //display connected stuff
      strcpy(display_line[FIRST_LINE], " WAITING  ");
      update_string(display_line[FIRST_LINE], FIRST_LINE);
      strcpy(display_line[SECOND_LINE], "   FOR    ");
      update_string(display_line[SECOND_LINE], SECOND_LINE);
      strcpy(display_line[THIRD_LINE], "   INPUT  ");
      update_string(display_line[THIRD_LINE], THIRD_LINE);
      strcpy(display_line[FOURTH_LINE], "          ");
      update_string(display_line[FOURTH_LINE], FOURTH_LINE);
      update_display = TRUE;
    }
    
    wheelsProcess();
    
    //Stopwatch
    if(!displayFirstTime){
      if(everySecond){
      HEXtoBCD(displayTime);
      for(int i=START_ELEMENT; i<FOUR_ELEMENTS; i++){
        display_line[FOURTH_LINE][i] = adc_char[i];
      }
    }
    }
  }
  //------------------------------------------------------------------------------
}

