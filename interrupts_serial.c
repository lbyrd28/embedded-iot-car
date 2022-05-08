//------------------------------------------------------------------------------
//  Filename: interrupts_serial.c
//
//  Description: This file contains all interrupts used for serial communication
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
extern volatile char UCA0_USB_Char_Rx[SMALL_RING_SIZE] = {RESET_STATE};
extern volatile char UCA0_USB_Char_Tx[SMALL_RING_SIZE] = {RESET_STATE};
extern volatile unsigned int UCA0_usb_tx_ring_wr = RESET_STATE;
extern volatile unsigned int UCA0_usb_tx_ring_rd = RESET_STATE;
extern volatile unsigned int UCA1_usb_tx_ring_wr = RESET_STATE;
extern volatile unsigned int UCA1_usb_tx_ring_rd = RESET_STATE;
extern volatile char UCA1_USB_Char_Rx[SMALL_RING_SIZE] = {RESET_STATE};
extern volatile char UCA1_USB_Char_Tx[SMALL_RING_SIZE] = {RESET_STATE};
extern volatile unsigned int UCA0_usb_rx_ring_wr = RESET_STATE;
extern volatile unsigned int UCA0_usb_rx_ring_rd = RESET_STATE;
extern volatile unsigned int UCA1_usb_rx_ring_wr = RESET_STATE;
extern volatile unsigned int UCA1_usb_rx_ring_rd = RESET_STATE;
extern volatile unsigned char PC_First_Char = FALSE;


//==============================================================================
//      UCA0 INTERRUPT - IOT
//==============================================================================

//------------------------------------------------------------------------------
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  unsigned int temp;
  char tempChar;
  switch(__even_in_range(UCA0IV,UCA_FLAG_INTERVAL)){
  case NO_UCA_FLAG: // Vector 0 - no interrupt
    break;
    //------------------------------------------------------------------------------
  case UCA_RX_FLAG: // Vector 2 - RXIFG
    temp = UCA0_usb_rx_ring_wr++; // Will copy to temp before incrementing
    if (UCA0_usb_rx_ring_wr >= SMALL_RING_SIZE){
      UCA0_usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    tempChar = UCA0RXBUF;
    UCA0_USB_Char_Rx[temp] = tempChar;
    UCA1TXBUF = tempChar;       // Echo Back
    break;
    //------------------------------------------------------------------------------    
  case UCA_TX_FLAG: // Vector 4 – TXIFG
    while(UCA0STATW & UCBUSY);
    temp = UCA0_usb_tx_ring_rd++;         // Will copy to temp before incrementing
    if (UCA0_usb_tx_ring_rd >= SMALL_RING_SIZE){
      UCA0_usb_tx_ring_rd = BEGINNING; // Circular buffer back to beginning
    }
    UCA0IE &= ~UCTXIE;                //disable further transmits 
    tempChar = UCA0_USB_Char_Tx[temp];
    UCA0TXBUF = tempChar;           //transmit the char
    break;
    //------------------------------------------------------------------------------    
  default: break;
  }
}
//------------------------------------------------------------------------------

//==============================================================================
//      UCA1 INTERRUPT - PC
//==============================================================================

//------------------------------------------------------------------------------
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  unsigned int temp;
  char tempChar;
  switch(__even_in_range(UCA1IV,UCA_FLAG_INTERVAL)){
  case NO_UCA_FLAG: // Vector 0 - no interrupt
    break;
    //------------------------------------------------------------------------------
  case UCA_RX_FLAG: // Vector 2 - RXIFG
    if(!PC_First_Char){  // Once PC sends its first char then we can start transmitting
      PC_First_Char = TRUE;
    }
    temp = UCA1_usb_rx_ring_wr++; // Will copy to temp before incrementing
    if (UCA1_usb_rx_ring_wr >= SMALL_RING_SIZE){
      UCA1_usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    tempChar = UCA1RXBUF;
    UCA1_USB_Char_Rx[temp] = tempChar;
    
    UCA0TXBUF = tempChar;   //send to PC so we can verify what we have received
    break;
    //------------------------------------------------------------------------------    
  case UCA_TX_FLAG: // Vector 4 – TXIFG
    if(!PC_First_Char) break; // Once PC sends its first char then we can start transmitting
    while(UCA1STATW & UCBUSY);
    temp = UCA1_usb_tx_ring_rd++;         // Will copy to temp before incrementing
       if (UCA1_usb_tx_ring_rd >= SMALL_RING_SIZE){
      UCA1_usb_tx_ring_rd = BEGINNING; // Circular buffer back to beginning
    }
    UCA1IE &= ~UCTXIE;                //disable further transmits 
    tempChar = UCA1_USB_Char_Tx[temp];
    UCA1TXBUF = tempChar;           //transmit the char to UCA0TX
    break;
    //------------------------------------------------------------------------------    
  default: break;
  }
}
//------------------------------------------------------------------------------

