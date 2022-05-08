//------------------------------------------------------------------------------
//  Filename: serial.c
//
//  Description: This file contains all functions for serial communication
//
//======================================================================================================
// TITLE: Enhanced Universal Serial Communication Interface (eUSCI) - UART mode
//        (Universal asynchronous receiver-transmitter)
//
// 2 Serial Ports: UCA0 (IOT communication) and UCA1 (PC Backend communication)
//
// Features include: 1) 7 or 8-bit data w/ odd, even, or no parity 2) Independent
// transmit and receive shift registers 3) MSB or LSB-first configurable transmit
// and receive 4)Independent interrupt capability for receive, transmit, start bit
// received, and transmit complete 5) Configurable baud rate
//
// Reccommeneded eUSCI_A initialization/ reconfig process: 1) Set UCSWRST high
// 2) Initialize all eUSCI_A registers while UCSWRST = 1 3) Configure ports 4) Clear
// UCSWRST 5) Enable interrupts using UCRXIE or UCTXIE
//
// CHARACTER FORMAT: Start bit -> 7 data bits -> 8th data bit (if UC7BIT = 0) ->
// Address bit (if UCMODEx = 10) -> Parity bit (if UCPEN = 1) -> Stop Bit -> 2nd Stop Bit (if
// UCSPB = 1)
//
// TRANSMIT INTERRUPT OPERATION: The UCTXIFG interrupt flag is set by the transmitter to indicate
// that UCAxTXBUF is ready to accept another character. An interrupt request is generated
// if UCTXIE and GIE are also set. UCTXIFG is automatically reset if a character is written to UCAxTXBUF.
// Flag is low if buffer is empty.
//
// RECEIVE INTERRUPT OPERTATION: The UCTXIFG interrupt flag is set by the transmitter to indicate that
// UCAxTXBUF is ready to accept another character. An interrupt request is generated if UCTXIE and
// GIE are also set. UCTXIFG is automatically reset if a character is written to UCAxTXBUF.
// Flag is low if buffer is empty.
//
// UART STATE CHANGE INTERRUPT FLAGS:
// -> UCSTTIFG = This flag is set when the UART module receives a START byte
// -> UCTXCPTIFG = Transmit complete interrupt. This flag is set, after the complete UART byte
// in the internal shift register including STOP bit got shifted out and UCAxTXBUF is empty
//
// UCAxIV Software Example:
// ---------------------------------------------------------------------------------
//  #pragma vector = USCI_A0_VECTOR __interrupt void USCI_A0_ISR(void) {
// switch(__even_in_range(UCA0IV,18)) {
// case 0x00: // Vector 0: No interrupts
// break;
// case 0x02: ... // Vector 2: UCRXIFG
// break;
// case 0x04: ... // Vector 4: UCTXIFG
// break;
// case 0x06: ... // Vector 6: UCSTTIFG
// break;
// case 0x08: ... // Vector 8: UCTXCPTIFG
// break;
// default: break;
//   }
// }
//---------------------------------------------------------------------------------
//
// UART REGISTERS:
//-------------------
//  UCAxCTLW0 Register:
//      Bit 15: UCPEN (Parity Enable)
//              0b = Parity disabled
//              1b = Parity enabled (generated in UCAxTXD and expected in UCAxRXD)
//      Bit 14: UCPAR (Parity Select)
//              0b = Odd Parity
//              1b = Even Parity
//      Bit 13: UCMSB (MSB first select)
//              0b = LSB first
//              1b = MSB first
//      Bit 12: UC7BIT (Character length)
//              0b = 8-bit data
//              1b = 7-bit data
//      Bit 11: UCSPB (Stop bit select)
//              0b = One stop bit
//              1b = Two stop bits
//      Bits 10-9: UCMODEx (selects asynchronous mode)
//              00b = UART mode
//              01b = Idle-line multiprocessor mode
//              10b = Address-bit multiprocessor mode
//              11b = UART mode with automatic baud-rate detection
//      Bit 8: UCSYNC (Synchronous mode enable)
//              0b = Asynchronous mode
//              1b = Synchronous mode
//      Bits 7-6: UCSSELx (Clock source select)
//              00b = UCLK
//              01b = Device specific
//              10b = SMCLK
//              11b = SMCLK
//      Bit 5: UCRXEIE (Receive erronous-character interrrupt enable)
//              0b = Erroneous characters rejected and UCRXIFG not set
//              1b = Erroneous characters recieved set UCRXIFG
//      Bit 4: UCBRKIE (Receive break character interrupt enable)
//              0b = Received break characters do not set UCRXIFG
//              1b = Received break characters set UCRXIFG
//      Bit 3: UCDORM (Dormant. Puts eUSCI_A into sleep mode)
//              0b = Not dormant. All received characters set UCRXIFG
//              1b = Dormant
//      Bit 2: UCTXADDR (Transmit address)
//              0b = Next frame transmitted is data
//              1 = Next frame transmitted is an address
//      Bit 1: UCTXBRK (Transmit break)
//      Bit 0: UCSWRST (Software reset enable)
//              0b = disabled - ready for operation
//              1b = enabled - held in reset state
// UCAxCTLW1 Register:
//      Bits 15-2: Reserved
//      Bits 1-0: UCGLITx (Deglitch time)
//              00b = 2ns
//              01b = 50ns
//              10b = 100ns
//              11b = 200ns
// UCSxBRW Register:
//      Bits 15-0: clock prescalar setting of the baud rate generater
// UCAxMCTLW Register:
//      Bits 15-8: UCBRSx (Second modulation stage select)
//      Bits 7-4: UCBRFx (First modulation stage select)
//      Bits 3-1: Reserved
//      Bit 0: Oversampling mode enable
//              0b = Disabled, 1b = enabled
// UCAxSTATW Register:
//      Bits 15-8: Reserved
//      Bit 7: UCLISTEN (Listen enable)
//              0b = disabled, 1b = enabled. UCAxTXD is internally fed back to receiver
//      Bit 6: UCFE (Framing error flag, cleared when RXBUF read)
//              0b = No error, 1b = character received with low stop bit
//      Bit 5: UCOE (Overrun error flag)
//      continue..............
//      Bit 0: UCBUSY (eUSCI_A busy, indicated if tramsit or receive in progress)
//              0b = inactive, 1b = currently transmitting/receving
// UCAxRXBUF Register:
//      Bits 15-8: Reserved
//      Bits 7-0: UCRXBUFx
// UCAxTXBUF Register
//      Bits 15-8: Reserved
//      Bits 7-0: UCTXBUFx
// UCAxIE Register
//      Bits 15-4: Reserved
//      Bit 3: UCTXCPTIE (Transmit complete interrupt enable)
//              0b = interrupt disabled, 1b = interrupt enabled
//      Bit 2: UCSTTIE (Start bit interrupt enable)
//      Bit 1: UCTXIE (Transmit interrupt enable)
//      Bit 0: UCRXIE (Receive interrupt enable)
//
//===========================================================================================================
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
extern volatile char UCA0_USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char UCA0_USB_Char_Tx[SMALL_RING_SIZE];
extern volatile unsigned int UCA0_usb_tx_ring_wr;
extern volatile unsigned int UCA0_usb_tx_ring_rd;
extern volatile unsigned int UCA1_usb_tx_ring_wr;
extern volatile unsigned int UCA1_usb_tx_ring_rd;
extern volatile char UCA1_USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char UCA1_USB_Char_Tx[SMALL_RING_SIZE];
extern volatile unsigned int UCA0_usb_rx_ring_wr;
extern volatile unsigned int UCA0_usb_rx_ring_rd;
extern volatile unsigned int UCA1_usb_rx_ring_wr;
extern volatile unsigned int UCA1_usb_rx_ring_rd;
unsigned char commandBuffer[COMMAND_ARRAY_LENGTH] = {RESET_STATE};
unsigned char commandBufferIndex = RESET_STATE;
extern char display_line[LCD_LINES][DISPLAYLENGTH];
unsigned char incomingChar = '\0';
unsigned char commandIncoming = FALSE;
extern volatile char displayFirstTime;
extern unsigned int next;



// Function prototypes
void clearUCA0Buffer(void);
void clearUCA1Buffer(void);
void baudUCA0(char rate);
void baudUCA1(char rate);
void Init_Serial(void);
void beginReceiveUCA0(void);
void beginReceiveUCA1(void);
void beginTransmitUCA0(void);
void beginTransmitUCA1(void);
char pullCharRXUCA0(void);
char pullCharRXUCA1(void);
void transmitStringUCA0(char * command);
void transmitStringUCA1(char * command);
void Project09Process(void);


//==============================================================================
//      INITIALIZATION
//==============================================================================

//----------------------------------------------------------------------------
void Init_Serial(void){
  //UCA0 Setup------------------------------------------------------------------
  UCA0CTLW0 |= UCSWRST;         // Set reset high
  UCA0CTLW0 = RESET_STATE;      // Reset register
  UCA0CTLW0 &= ~UCPEN;          // Disable Parity Bit
  UCA0CTLW0 &= ~UCMSB;          // LSB first
  UCA0CTLW0 &= ~UC7BIT;         // 8 bit word
  UCA0CTLW0 &= ~UCSPB;          // 1 stop bit
  UCA0CTLW0 |= UCMODE_0;        // UART mode
  UCA0CTLW0 &= ~UCSYNC;         // Asynchronous mode
  UCA0CTLW0 |= UCSSEL__SMCLK;   // Set SMCLK as fBRCLK
  
  baudUCA0(BAUD_115200);
  clearUCA0Buffer();
  UCA0IE |= UCRXIE;             //RX interrupt enabled - ready to receive
  
  //UCA1 Setup--------------------------------------------------------------------
  UCA1CTLW0 |= UCSWRST;         // Set reset high
  UCA1CTLW0 = RESET_STATE;      // Reset register
  UCA1CTLW0 &= ~UCPEN;          // Disable Parity Bit
  UCA1CTLW0 &= ~UCMSB;          // LSB first
  UCA1CTLW0 &= ~UC7BIT;         // 8 bit word
  UCA1CTLW0 &= ~UCSPB;          // 1 stop bit
  UCA1CTLW0 |= UCMODE_0;        // UART mode
  UCA1CTLW0 &= ~UCSYNC;         // Asynchronous mode
  UCA1CTLW0 |= UCSSEL__SMCLK;   // Set SMCLK as fBRCLK
  
  baudUCA1(BAUD_115200);
  clearUCA1Buffer();  
  UCA1IE |= UCRXIE;             //RX interrupt enabled - ready to receive
  
}
//------------------------------------------------------------------------------

//==============================================================================
//      CHANGE BAUD RATE
//==============================================================================

//----------------------------------------------------------------------------
void baudUCA0(char rate){
  UCA0CTLW0 |= UCSWRST;         //Reset high to allow change
  switch(rate){
  case BAUD_115200:
    UCA0BRW = BRW_115200;               
    UCA0MCTLW = MCTLW_115200;           
    break;
  case BAUD_460800:
    UCA0BRW = BRW_460800;               
    UCA0MCTLW = MCTLW_460800;          
    break;
  case BAUD_9600:
    UCA0BRW = BRW_9600;
    UCA0MCTLW = MCTLW_9600;
    break;
  default: break;
  }
  UCA0CTLW0 &= ~UCSWRST;         // Reset disabled
  UCA0IE |= UCRXIE;     // Receive interrupt needs to be set high again
}
//------------------------------------------------------------------------------

//----------------------------------------------------------------------------
void baudUCA1(char rate){
  UCA1CTLW0 |= UCSWRST;         //Reset high to allow change
  switch(rate){
  case BAUD_115200:
    UCA1BRW = BRW_115200;               
    UCA1MCTLW = MCTLW_115200;           
    break;
  case BAUD_460800:
    UCA1BRW = BRW_460800;               
    UCA1MCTLW = MCTLW_460800;          
    break;
  case BAUD_9600:
    UCA1BRW = BRW_9600;
    UCA1MCTLW = MCTLW_9600;
    break;
  default: break;
  }
  UCA1CTLW0 &= ~UCSWRST;         // Reset disabled
  UCA1IE |= UCRXIE;     // Receive interrupt needs to be set high again
}
//------------------------------------------------------------------------------

//==============================================================================
//      CLEAR BUFFER FUNCTIONS
//==============================================================================

//----------------------------------------------------------------------------
void clearUCA0Buffer(void){
  int i;                                        //counter
  //clear small ring buffer (size depends on macro)
  for(i=BEGINNING; i<SMALL_RING_SIZE; i++){
    UCA0_USB_Char_Rx[i] = RESET_STATE;               // USB Rx Buffer
    UCA0_USB_Char_Tx[i] = RESET_STATE;                // USB Tx Buffer
  }
  
  //reset read and write positions
  UCA0_usb_tx_ring_wr = BEGINNING;
  UCA0_usb_tx_ring_rd = BEGINNING;
}
//------------------------------------------------------------------------------

//----------------------------------------------------------------------------
void clearUCA1Buffer(void){
  int i;                                        //counter
  //clear small ring buffer (size depends on macro)
  for(i=BEGINNING; i<SMALL_RING_SIZE; i++){
    UCA1_USB_Char_Rx[i] = RESET_STATE;               // USB Rx Buffer
    UCA1_USB_Char_Tx[i] = RESET_STATE;                // USB Tx Buffer
  }
  
  //reset read and write positions
  UCA1_usb_tx_ring_wr = BEGINNING;
  UCA1_usb_tx_ring_rd = BEGINNING;
}
//------------------------------------------------------------------------------

//==============================================================================
//      SEND AND RECEIVE FUNCTIONS
//==============================================================================

//------------------------------------------------------------------------------
void beginReceiveUCA0(void) {
  clearUCA0Buffer();
  UCA0IE |= UCRXIE;                //enable the receive interrupt
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void beginReceiveUCA1(void) {
  clearUCA1Buffer();
  UCA1IE |= UCRXIE;                //enable the receive interrupt
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void beginTransmitUCA0(void) {
  UCA0IFG |= UCTXIFG;              //raise flag manually
  UCA0IE |= UCTXIE;                //enable the transmit interrupt
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void beginTransmitUCA1(void) {
  UCA1IFG |= UCTXIFG;              //raise flag manually
  UCA1IE |= UCTXIE;                //enable the transmit interrupt
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Takes current character out of RX Buffer and returns it
// Clears out current buffer position
// Increments read index
char pullCharRXUCA0(void) {
  char character;
  character = UCA0_USB_Char_Rx[UCA0_usb_rx_ring_rd];    //Get current rx character
  UCA0_USB_Char_Rx[UCA0_usb_rx_ring_rd] = FALSE;        //Clear it
  UCA0_usb_rx_ring_rd++;
  if(UCA0_usb_rx_ring_rd >= SMALL_RING_SIZE) {      //Prevent going over
    UCA0_usb_rx_ring_rd = RESET_STATE;
  }
  return character;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Takes current character out of RX Buffer and returns it
// Clears out current buffer position
// Increments read index
char pullCharRXUCA1(void) {
  char character;
  character = UCA1_USB_Char_Rx[UCA1_usb_rx_ring_rd];    //Get current rx character
  UCA1_USB_Char_Rx[UCA1_usb_rx_ring_rd] = FALSE;        //Clear it
  UCA1_usb_rx_ring_rd++;
  if(UCA1_usb_rx_ring_rd >= SMALL_RING_SIZE) {      //Prevent going over
    UCA1_usb_rx_ring_rd = RESET_STATE;
  }
  return character;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Process to prepare a single character to go to TXBUF
// Will be used incrementally for the transmit string operation
void prepareTXCharUCA0(char c) {
  UCA0_USB_Char_Tx[UCA0_usb_tx_ring_wr] = c;            //input character to TX array
  UCA0_usb_tx_ring_wr++;                            //increment to prepare for next char
  if(UCA0_usb_tx_ring_wr >= SMALL_RING_SIZE){       //don't overflow
    UCA0_usb_tx_ring_wr = RESET_STATE;
  }
}
//----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Process to prepare a single character to go to TXBUF
// Will be used incrementally for the transmit string operation
void prepareTXCharUCA1(char c) {
  UCA1_USB_Char_Tx[UCA1_usb_tx_ring_wr] = c;            //input character to TX array
  UCA1_usb_tx_ring_wr++;                            //increment to prepare for next char
  if(UCA1_usb_tx_ring_wr >= SMALL_RING_SIZE){       //don't overflow
    UCA1_usb_tx_ring_wr = RESET_STATE;
  }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// For transmitting a string using single char functions defined prevoiously
// Length is taken and once limit reached for loop stops and interrupt ends
void transmitStringUCA0(char * command){
  int i;    //counter
  int stringlength; //string length
  stringlength =strlen(command); //charsleft is global volatile
  for(i=BEGINNING; i<stringlength; i++) {
    prepareTXCharUCA0(command[i]);
    beginTransmitUCA0();
  }
  
}
//------------------------------------------------------------------------------    

//------------------------------------------------------------------------------
// For transmitting a string using single char functions defined prevoiously
// Length is taken and once limit reached for loop stops and interrupt ends
void transmitStringUCA1(char * command){
  int i;    //counter
  int stringlength; //string length
  stringlength = strlen(command);  
  for(i=BEGINNING; i<stringlength; i++) {
    prepareTXCharUCA1(command[i]);
    beginTransmitUCA1();
  }
  
}
//------------------------------------------------------------------------------    

//==============================================================================
//      PROJECT 09 PROCESS
//==============================================================================

char start = FALSE;

void Project09Process(void){
  
  //MAC ADDRESS: 20:f8:5e:fd:74:d5
  //IP ADDRESS: 10.123.20.65
  //PORT: 1024
  //SSID: d8:b1:90:a6:63:d1
  
  
  incomingChar = pullCharRXUCA0(); //get character off rx buffer
  if(incomingChar == '^'){  //command signify character
    commandIncoming = TRUE;
  }
  
  if(commandIncoming){
    commandBuffer[commandBufferIndex++] = incomingChar;
  }
  
  if(commandIncoming && incomingChar == '\r'){
    commandIncoming = FALSE;
    commandBufferIndex = RESET_STATE;
    start = TRUE;
  }
  
  
  
  
  //if we just got the ^ we will not enter yet until next cycle
  if(start){
    switch(commandBuffer[FIRST]){
    case '^': //test if working
      transmitStringUCA1("I'm Here");
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'F': //forward
      RIGHT_FORWARD_SPEED = FULL_SPEED;
      LEFT_FORWARD_SPEED = FULL_SPEED;
      if(displayFirstTime){
        displayFirstTime = FALSE;
        strcpy(display_line[SECOND_LINE], "IP ADR: 10");
        strcpy(display_line[THIRD_LINE], ".123.20.65");
      }
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'R': //reverse
      RIGHT_REVERSE_SPEED = FULL_SPEED;
      LEFT_REVERSE_SPEED = FULL_SPEED;
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'L': //left turn
      RIGHT_FORWARD_SPEED = MAKEUP_SPEED;
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'X': //Right Turn
      LEFT_FORWARD_SPEED = MAKEUP_SPEED;
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'S': //Stop
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'A': //Ping
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '1': 
      strcpy(display_line[FIRST_LINE], "Arrived 1 ");
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '2': 
      display_line[FIRST_LINE][MARKER_CHAR] = '2';
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '3': 
      display_line[FIRST_LINE][MARKER_CHAR] = '3';
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '4': 
      display_line[FIRST_LINE][MARKER_CHAR] = '4';
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '5': 
      display_line[FIRST_LINE][MARKER_CHAR] = '5';
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '6': 
      display_line[FIRST_LINE][MARKER_CHAR] = '6';
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '7': 
      display_line[FIRST_LINE][MARKER_CHAR] = '7';
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case '8': 
      display_line[FIRST_LINE][MARKER_CHAR] = '8';
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'B': //start black line
      P5OUT |= IR_LED; // Turn on
      delayFor100ms(PASSED_200MS);
      next = TENTH;
      commandBuffer[FIRST] = RESET_STATE;
      break;
    case 'E': //exit black line
      next = SIXTH;
      commandBuffer[FIRST] = RESET_STATE;
      break;
    default: break;
    }
    if(commandBuffer[SECOND] == '^'){
      commandBuffer[FIRST] = commandBuffer[THIRD];
      commandBuffer[SECOND] = '\0';
    }
    else{
      start=FALSE;
    }
  }
  
  
  
  
}
