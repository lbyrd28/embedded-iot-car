//------------------------------------------------------------------------------
//  Filename: ports.c
//
//  Description: This file contains the initialization of ports
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

// Function Prototypes
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);
  
//===========================================================================================
//===========================================================================================


//Main function that intializes all the ports
void Init_Ports(void){
  //------------------------------------------------------------------------------
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_Port5();
  Init_Port6();
  //------------------------------------------------------------------------------
}

//Port 1 Initializations
void Init_Port1(void){
  //------------------------------------------------------------------------------
  // Configure PORT 1
  P1DIR = OUTPUT; // Set P1 direction to output
  P1OUT = OUT_VAL_LOW; // P1 set Low
  // P1 PIN 0
  P1SEL0 &= ~RedLED; //RedLED GPIO operation
  P1SEL1 &= ~RedLED; //RedLED GPIO operation
  P1DIR |= RedLED; // Direction = output
  P1OUT &= ~RedLED; //set off
  // P1 PIN 1
  P1SEL0 |= A1_SEEED; // A1 operation 
  P1SEL1 |= A1_SEEED; // A1 operation 
  P1DIR &= ~A1_SEEED; // input
  // P1 PIN 2
  P1SEL0 |= V_DETECT_L; // A2 operation - ADC input for V_DETECT_L
  P1SEL1 |=V_DETECT_L; // A2 operation - ADC input for V_DETECT_L 
  P1DIR &= ~V_DETECT_L; // input
  // P1 PIN 3
  P1SEL0 |= V_DETECT_R; // A3 operation  - ADC input for V_DETECT_R
  P1SEL1 |= V_DETECT_R; // A3 operation  - ADC input for V_DETECT_R 
  P1DIR &= ~V_DETECT_R; // input
  // P1 PIN 4
  P1SEL0 |= V_BAT; // A4 operation - ADC input for V_BAT
  P1SEL1 |= V_BAT; // A4 operation - ADC input for V_BAT 
  P1DIR &= ~V_BAT; // input
  // P1 PIN 5
  P1SEL0 |= V_THUMB; // A5 operation  - ADC input for V_THUMB
  P1SEL1 |= V_THUMB; // A5 operation  - ADC input for V_THUMB
  P1DIR &= ~V_THUMB; // input
  // P1 PIN 6
  P1SEL0 |= UCA0RXD; // UCA0RXD operation 
  P1SEL1 &= ~UCA0RXD; // UCA0RXD operation 
  P1DIR &= ~UCA0RXD; // input
  // P1 PIN 7
  P1SEL0 |= UCA0TXD; // UCA0TXD operation 
  P1SEL1 &= ~UCA0TXD; // UCA0TXD operation
  P1DIR &= ~UCA0TXD; // input 
  //------------------------------------------------------------------------------
}

//Port 2 Initializations
void Init_Port2(void){
  //------------------------------------------------------------------------------
  P2DIR = OUTPUT; // Set P1 direction to output
  P2OUT = OUT_VAL_LOW; // P1 set Low
  // P2 PIN 0
  P2SEL0 &= ~P2_0; // P2_0 GPIO operation
  P2SEL1 &= ~P2_0; // P2_0 GPIO operation
  P2DIR &= ~P2_0; // Direction = input
  // P2 PIN 1
  P2SEL0 &= ~P2_1; // P2_1 GPIO operation
  P2SEL1 &= ~P2_1; // P2_1 GPIO operation
  P2DIR &= ~P2_1; // Direction = input
  // P2 PIN 2
  P2SEL0 &= ~P2_2; // P2_2 GPIO operation
  P2SEL1 &= ~P2_2; // P2_2 GPIO operation
  P2DIR &= ~P2_2; // Direction = input
  // P2 PIN 3
  P2SEL0 &= ~SW2; // SW2 Operation
  P2SEL1 &= ~SW2; // SW2 Operation
  P2DIR &= ~SW2; // Direction = input
  P2OUT |= SW2; // Configure pullup resistor
  P2REN |= SW2; // Enable pullup resistor
  P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
  P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
  P2IE |= SW2; // P2.6 interrupt enabled
  // P2 PIN 4
  P2SEL0 &= ~P2_4; // P2_4 GPIO operation
  P2SEL1 &= ~P2_4; // P2_4 GPIO operation
  P2DIR &= ~P2_4; // Direction = input
  // P2 PIN 5
  P2SEL0 &= ~P2_5; // P2_5 GPIO operation
  P2SEL1 &= ~P2_5; // P2_5 GPIO operation
  P2DIR &= ~P2_5; // Direction = input
  // P2 PIN 6
  P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
  P2SEL1 |= LFXOUT; // LFXOUT Clock operation
  // P2 PIN 7
  P2SEL0 &= ~LFXIN; // LFXIN Clock operation
  P2SEL1 |= LFXIN; // LFXIN Clock operation
  //------------------------------------------------------------------------------
}

//Port 3 Initializations
void Init_Port3(void){
  //------------------------------------------------------------------------------
  // Configure PORT 3
  P3DIR = OUTPUT; // Set P3 direction to output
  P3OUT = OUT_VAL_LOW; // P3 set Low
  // P3 PIN 0
  P3SEL0 &= ~TEST_PROBE; //TEST_PROBE GPIO operation
  P3SEL1 &= ~TEST_PROBE; //TEST_PROBE GPIO operation
  P3OUT &= ~TEST_PROBE; //set low (off)
  P3DIR |= TEST_PROBE; // Direction = output
  // P3 PIN 1
  P3SEL0 |= OA20; // OA20 operation 
  P3SEL1 |= OA20; // OA20 operation
  P3DIR &= ~OA20; // input 
  // P3 PIN 2
  P3SEL0 |= OA2N; // OA2N
  P3SEL1 |= OA2N; // OA2n
  P3DIR &= ~OA2N; //Direction = input
  // P3 PIN 3
  P3SEL0 |= OA2P; // OA2P
  P3SEL1 |= OA2P; // OA2P
  P3DIR &= ~OA2P; //Direction = input
  // P3 PIN 4
  P3SEL0 |= SMCLK_OUT; // SMCLK
  P3SEL1 &= ~SMCLK_OUT; //SMCLK
  P3OUT |= SMCLK_OUT; //Direction = output
  // P3 PIN 5
  P3SEL0 &= ~P3_5; // GPIO
  P3SEL1 &= ~P3_5; // GPIO
  P3DIR &= ~P3_5; //input
  // P3 PIN 6
  P3SEL0 &= ~IOT_LINK; // GPIO
  P3SEL1 &= ~IOT_LINK; // GPIO
  P3OUT &=  ~IOT_LINK; // Direction = input
  // P3 PIN 7
  P3SEL0 &= ~P3_7; // GPIO operation
  P3SEL1 &= ~P3_7; // GPIO operation
  P3DIR |= P3_7; // Direction = output
  //------------------------------------------------------------------------------
}

//Port 4 Initializations
void Init_Port4(void){
  //------------------------------------------------------------------------------
  // Configure PORT 4
  P4DIR = OUTPUT; // Set P1 direction to output
  P4OUT = OUT_VAL_LOW; // P1 set Low
  // P4 PIN 0
  P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
  P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]
  // P4 PIN 1
  P4SEL0 &= ~SW1; // SW1 GPIO operation
  P4SEL1 &= ~SW1; // SW1 GPIO operation
  P4DIR &= ~SW1; // Direction = input
  P4OUT |= SW1; // Configure pullup resistor
  P4REN |= SW1; // Enable pullup resistor
  P4IES |= SW1; // P2.0 Hi/Lo edge interrupt
  P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
  P4IE |= SW1; // P2.6 interrupt enabled
  // P4 PIN 2
  P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
  // P4 PIN 3
  P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
  // P4 PIN 4
  P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
  P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
  // P4 PIN 5
  P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
  // P4 PIN 6
  P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
  // P4 PIN 7
  P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
  //------------------------------------------------------------------------------
}

//Port 5 Initializations
void Init_Port5(void){
  //------------------------------------------------------------------------------
  // Configure PORT 5
  P5DIR = OUTPUT; // Set P5 direction to output
  P5OUT = OUT_VAL_LOW; // P5 set Low
  // P5 PIN 0
  P5SEL0 &= ~IOT_RESET; // GPIO
  P5SEL1 &= ~IOT_RESET; // GPIO
  P5OUT &= ~IOT_RESET; // Reset the IOT by driving low
  P5DIR |= IOT_RESET; // Set direction to output
  // P5 PIN 1
  P5SEL0 &= ~IR_LED; // GPIO
  P5SEL1 &= ~IR_LED; // GPIO
  P5DIR |= IR_LED; // Set to output
  P5OUT &=~ IR_LED; // Turn off
  // P5 PIN 2
  P5SEL0 &= ~IOT_PROG_SEL; // GPIO
  P5SEL1 &= ~IOT_PROG_SEL; // GPIO
  P5DIR &= ~IOT_PROG_SEL; // Set direction to input
  // P5 PIN 3
  P5SEL0 &= ~IOT_PROG_MODE; // GPIO
  P5SEL1 &= ~IOT_PROG_MODE; // GPIO
  P5DIR &= ~IOT_PROG_MODE; // Set direction to input
  // P5 PIN 4
   P5SEL0 &= ~CHECK_BAT; // Set to GP I/O
  P5SEL1 &= ~CHECK_BAT; // Set to GP I/O
  P5DIR &= ~CHECK_BAT; // Set direction to input
  //------------------------------------------------------------------------------
}

//Port 6 Initializations
void Init_Port6(void){
  //------------------------------------------------------------------------------
  // Configure PORT 6
  P6DIR = OUTPUT; // Set P6 direction to output
  P6OUT = OUT_VAL_LOW; // P6 set Low
  // P6 PIN 0
  P6SEL0 |= R_FORWARD; // PWM
  P6SEL1 &= ~R_FORWARD; // PWM
  P6DIR |= R_FORWARD; // Set direction to output
  // P6 PIN 1
  P6SEL0 |= L_FORWARD; // PWM
  P6SEL1 &= ~L_FORWARD; // PWM
  P6DIR |= L_FORWARD; // Set direction to output
  // P6 PIN 2
  P6SEL0 |= R_REVERSE; // PWM
  P6SEL1 &= ~R_REVERSE; // PWM
  P6DIR |= R_REVERSE; // Set direction to output
  // P6 PIN 3
  P6SEL0 |= L_REVERSE; // PWM
  P6SEL1 &= ~L_REVERSE; // PWM
  P6DIR |= L_REVERSE; // Set direction to output
  // P6 PIN 4
  P6SEL0 &= ~LCD_BACKLITE; // Set GP I/O for LCD_BACKLITE
  P6SEL1 &= ~LCD_BACKLITE; // Set GP I/O for LCD_BACKLITE
  P6OUT |= LCD_BACKLITE; // Set LCD_BACKLITE on [High]
  P6DIR |= LCD_BACKLITE; // Set LCD_BACKLITE direction to output
  // P6 PIN 5
  P6SEL0 &= ~P6_5; // Set GP I/O 
  P6SEL1 &= ~P6_5; // Set GP I/O 
  P6DIR |= P6_5; //output
  // P6 PIN 6
  P6SEL0 &= ~GRN_LED; // GRN_LED as GP I/O
  P6SEL1 &= ~GRN_LED; // GRN_LED as GP I/O
  P6OUT |= GRN_LED; // Set Green LED on
  P6DIR |= GRN_LED; // Set Green LED direction to output
  //------------------------------------------------------------------------------
}