//------------------------------------------------------------------------------
//  Filename: ADC.c
//
//  Description: This file contains the functions needed to run the ADC
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
extern volatile unsigned int ADC_Thumb = RESET_STATE;
extern volatile unsigned int ADC_LeftDetector = RESET_STATE;
extern volatile unsigned int ADC_RightDetector = RESET_STATE;
extern volatile unsigned int ADC_Bat = RESET_STATE;
extern char display_line[LCD_LINES][DISPLAYLENGTH];

//==============================================================================
// Initiliaztion
//==============================================================================

void Init_ADC(void){
  //------------------------------------------------------------------------------
  // V_DETECT_L (0x04) // Pin 2 A2
  // V_DETECT_R (0x08) // Pin 3 A3
  // V_THUMB (0x20) // Pin 5 A5
  //------------------------------------------------------------------------------
  // ADCCTL0 Register
 ADCCTL0 = RESET_STATE; // Reset
 ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
 ADCCTL0 |= ADCMSC; // MSC
 ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
 ADCCTL2 = RESET_STATE; // Reset
 ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
 ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
 ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
 ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
 ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
 ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
 ADCCTL2 = RESET_STATE; // Reset
 ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
 ADCCTL2 |= ADCRES_1; // ADC resolution  = 10 bit 
 ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
 ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
 ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
 ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
 ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
 ADCCTL0 |= ADCENC; // ADC enable conversion.
 ADCCTL0 |= ADCSC; // ADC start conversion.

}


//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------

extern char adc_char[END1] = {RESET_STATE};

void HEXtoBCD(int hex_value){
  int value=RESET_STATE;
  adc_char[FIRST_CHAR_ADC] = '0';
  int i;
  
  //Clear ADC array
  for(i=BEGINNING; i<END1; i++){
    adc_char[i] = RESET;
  }
  
  while (hex_value > THOUSANDTHS_END){
    hex_value = hex_value - THOUSANDTHS;
    value = value + NEXT;
    
  }
  adc_char[BEGINNING] = ADD_HEX + value;
  
  value = RESET_STATE;
  while (hex_value > HUNDREDS_END){
    hex_value = hex_value - HUNDREDS;
    value = value + NEXT;
    
  }
  adc_char[FIRST] = ADD_HEX + value;
  value = RESET_STATE;
  while (hex_value > TENTHS_END){
    hex_value = hex_value - TENTHS;
    value = value + NEXT;
    
  }
  adc_char[SECOND] = ADD_HEX + value;
  adc_char[THIRD] = ADD_HEX + hex_value;
}
//******************************************************************************
//------------------------------------------------------------------------------


//==============================================================================
// Function to Display ADC Values on LCD
//==============================================================================

void ADC_Display_Process(void){
  
  int i;
  
  //For Thumbwheel - Not needed now
  /*
  HEXtoBCD(ADC_Thumb);
  
  for(i=START_ELEMENT; i<FOUR_ELEMENTS; i++){
  display_line[FIRST_LINE][i] = adc_char[i];
}  
  */
  
  HEXtoBCD(ADC_RightDetector);
  
  for(i=START_ELEMENT; i<FOUR_ELEMENTS; i++){
    display_line[SECOND_LINE][i] = adc_char[i];
  }
  
  HEXtoBCD(ADC_LeftDetector);
  for(i=START_ELEMENT; i<FOUR_ELEMENTS; i++){
    display_line[FIRST_LINE][i] = adc_char[i];
  }
  
  display_line[FIRST_LINE][TENTH_CHAR] = 'T';
  display_line[FIRST_LINE][NINTH_CHAR] = 'F';
  display_line[FIRST_LINE][EIGHTH_CHAR] = 'E';
  display_line[FIRST_LINE][SEVENTH_CHAR] = 'L';
  
  display_line[SECOND_LINE][TENTH_CHAR] = 'T';
  display_line[SECOND_LINE][NINTH_CHAR] = 'H';
  display_line[SECOND_LINE][EIGHTH_CHAR] = 'G';
  display_line[SECOND_LINE][SEVENTH_CHAR] = 'I';
  display_line[SECOND_LINE][SIXTH_CHAR] = 'R';
}
