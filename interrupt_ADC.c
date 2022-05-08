//------------------------------------------------------------------------------
//  Filename: interrupt_ADC.c
//
//  Description: This file contains the interrupt to run the ADC
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

// Global variables
volatile unsigned char ADC_Channel = RESET_STATE;
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_LeftDetector;
extern volatile unsigned int ADC_RightDetector;
extern volatile unsigned int ADC_Bat;


#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
  case ADCIV_NONE:
    break;
  case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
    // before its previous conversion result was read.
    break;
  case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
    break;
  case ADCIV_ADCHIIFG: // Window comparator interrupt flags
    break;
  case ADCIV_ADCLOIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCINIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
    ADCCTL0 &= ~ADCENC;     // Toggle ENC Bit
    switch (ADC_Channel++){
    case CHANNEL_A0:
      ADCMCTL0 &= ~ADCINCH_2;       // Last channel A2
      ADCMCTL0 |= ADCINCH_3;       // Next channel A3
      ADC_LeftDetector = ADCMEM0;   //Channel A0
      ADC_LeftDetector = ADC_LeftDetector >> LAST_BIT;        //Slice off last 1 bits
      break;
    case CHANNEL_A1:
      ADCMCTL0 &= ~ADCINCH_3;       // Last channel A3
      ADCMCTL0 |= ADCINCH_4;       // Next channel A4
      ADC_RightDetector = ADCMEM0;   //Channel A1
      ADC_RightDetector = ADC_RightDetector >> LAST_BIT;        //Slice off last 1 bits
      break;
    case CHANNEL_A2:
      ADCMCTL0 &= ~ADCINCH_4;       // Last channel A4
      ADCMCTL0 |= ADCINCH_5;       // Next channel A5
      ADC_Bat = ADCMEM0;   //Channel A4
      break;
    case CHANNEL_A3:
      ADCMCTL0 &= ~ADCINCH_5;       // Last channel A5
      ADCMCTL0 |= ADCINCH_2;       // Next channel A2
      ADC_Thumb = ADCMEM0;   //Channel A3
      break;
    default:
      break;
    }
    ADCCTL0 |= ADCENC;  // Enable Conversions
    ADCCTL0 |= ADCSC;   // Start next sample
    break;
  default:
    break;
  }
}


