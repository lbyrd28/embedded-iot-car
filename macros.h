//------------------------------------------------------------------------------
//  Filename: macros.h
//
//  Description: This file contains all the macros used for each project.
//
//
//  Logan Byrd
//  Oct 2019
//  Built with IAR Embedded Workbench Version: V7.12.4
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//==============================================================================
//      GIVEN MAIN MACROS
//==============================================================================

#define RED_LED_ON      (P1OUT |= RED_LED)
#define RED_LED_OFF    (P1OUT &= ~RED_LED)
#define GREEN_LED_ON    (P6OUT |= GRN_LED)
#define GREEN_LED_OFF  (P6OUT &= ~GRN_LED)
#define ALWAYS                         (1)
#define RESET_STATE                    (0)
#define RED_LED                     (0x01) // RED LED 0
#define GRN_LED                     (0x40) // GREEN LED 1

//==============================================================================
//      GIVEN MAIN MACROS
//==============================================================================

#define FIRST_TRIAL_PASSED (250)
#define SECOND_TRIAL_PASSED (200)
#define THIRD_TRIAL_PASSED (150)
#define FOURTH_TRIAL_PASSED (100)
#define FIFTH_TRIAL_PASSED (50)

//==============================================================================
//      CLOCKS MACROS
//==============================================================================

#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)
#define DELAY_CYCLES (3)
#define FALSE        (0)
#define ONE_FILLS          (0xffff)
#define FREQ_TRIM    (3)
#define FREQ_CUTOFF  (4)
#define DCO_TAP       (256)
#define FREQMULT      (3000)
#define NINE_BIT_TRUE    (0x01ff)
#define CUT_OFF_LAST_4 (0x0070)
#define FREQADD         (243)


//==============================================================================
//      LCD DISPlAY MACROS
//==============================================================================

#define FIRST_LINE      (0)
#define SECOND_LINE     (1)
#define THIRD_LINE      (2)
#define FOURTH_LINE     (3)
#define LCD_LINES      (4)
#define DISPLAYLENGTH (11)
#define TRUE            (1)
#define THREE_LINES     (3)
#define BEGIN           (0)
#define BEGIN_LINE      (0)
#define END_LINE        (10)

//==============================================================================
//      PORT MACROS
//==============================================================================

// Port 1 Pins
#define RedLED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2
#define V_DETECT_R (0x08) // 3
#define V_BAT (0x10) // 1 A4_SEEED
#define V_THUMB (0x20) // 5
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

//Port 2 Pins
#define P2_0 (0x01) // 0
#define P2_1 (0x02) // 1
#define P2_2 (0x04) // 2
#define SW2 (0x08) // 3 SW2
#define P2_4 (0x10) // 4
#define P2_5 (0x20) // 5
#define LFXOUT (0x40) // XOUTR
#define LFXIN (0x80) // XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define OA20 (0x02) // 1 Photodiode Circuit
#define OA2N (0x04) // 2 Photodiode Circuit
#define OA2P (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT (0x10) // 4 SMCLK
#define P3_5 (0x20) // 5
#define IOT_LINK (0x40) // 6 IOT_LINK
#define P3_7 (0x80) // 7

// Port 4 Pins
#define RESET_LCD (0x01) // 0 LCD Reset
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

// Port 5 Pins
#define IOT_RESET (0x01) // Resets the IOT Module
#define IR_LED (0x02) // Turns on the IR detector LED(s)
#define IOT_PROG_SEL (0x04) // Used for IOT programming
#define IOT_PROG_MODE (0x08) // Used for IOT Programming
#define CHECK_BAT (0x10) // Checks battery voltage


//Port 6 Pins
#define R_FORWARD (0x01) // Turns Right Wheel forward
#define L_FORWARD (0x02) // Turns Left Wheel Forward
#define R_REVERSE (0x04) // Turns Right Wheel Backward
#define L_REVERSE (0x08) // Turns Left Wheel Backward
#define LCD_BACKLITE (0x10) // Turns LCD Backlite on
#define P6_5 (0x20) // 6
#define GRN_LED (0x40) // Green LED control


//Other Defines
#define RESET (0x00) //Used for GPIO select bits
#define OUTPUT (0xFF) //Used for defining pin direction as output
#define INPUT (0x00) //Used for defining pin direction as input
#define OUT_VAL_LOW (0x00) //Used for setting POUT initial value as "low"
#define OUT_VAL_HIGH (0xFF) //POUT = 1
#define PULLUP  (0x00) // for pullup resistor


//==============================================================================
//      SHAPES MACROS
//==============================================================================

#define CIRCLE                          (1)
#define TRIANGLE                        (2)
#define FIG8                            (3)
#define TIME_MAX                        (10)
#define RIGHT_WHEEL_ON_STRAIGHT         (8)
#define LEFT_WHEEL_ON_STRAIGHT          (8)
#define RIGHT_WHEEL_ON_CIRCLE           (8)
#define LEFT_WHEEL_ON_CIRCLE            (2)
#define WAIT                            (1)
#define START                           (2)
#define DONE                            (3)
#define WAIT_DONE                       (60)
#define CIRCLE_DONE                     (220)
#define LOOP_DONE                       (1000)
#define TURN                            (4)
#define STRAIGHT                        (5)
#define FIRST_STRAIGHT_DONE             (15)
#define TURN_DONE                       (73)
#define FINISHED_STRAIGHTS              (6)
#define LEFT_CIRCLE                     (6)
#define RIGHT_CIRCLE                    (7)
#define LEFT_CIRCLE_TIME                (82)
#define RIGHT_CIRCLE_TIME               (82)
#define LEFT_CIRCLE_SPEED_LEFT          (9)
#define LEFT_CIRCLE_SPEED_RIGHT         (1)
#define RIGHT_CIRCLE_SPEED_LEFT         (1)
#define RIGHT_CIRCLE_SPEED_RIGHT        (9)
#define FIG8DONE                        (2)



//==============================================================================
//      TIMER MACROS
//==============================================================================

#define NO_INTERRUPT                    (0)
#define CCR1                            (2)
#define CCR2                            (4)
#define CCR3                            (6)
#define CCR4                            (8)
#define CCR5                            (10)
#define CCR6                            (12) 
#define OVERFLOW                        (14)
#define GO_THRU_CCR                     (14)
#define PASSED_100MS                    (1)
#define PASSED_200MS                    (2)
#define PASSED_800MS                    (8)
#define PASSED_1S                       (10)
#define PASSED_2S                       (20)
#define PASSED_5S                       (50)
#define TB0CCR0_INTERVAL                (50000) //100ms
#define TB0CCR1_INTERVAL                (50000) //100ms
#define SWITCH1_DEBOUNCE_TIME           (10)    //1000 ms
#define SWITCH2_DEBOUNCE_TIME           (10)    //1000 ms

//==============================================================================
//		PROJECT 5 MACROS
//==============================================================================

#define ONE_SEC							(10)
#define TWO_SEC							(20)
#define THREE_SEC						(30)
#define FIRST							(1)
#define SECOND							(2)
#define THIRD							(3)
#define FOURTH							(4)
#define FIFTH							(5)
#define SIXTH							(6)
#define SEVENTH							(7)
#define EIGHTH							(8)
#define NINTH							(9)
#define TENTH							(10)
#define ELEVENTH						(11)
#define TWELVETH						(12)
#define LAST_BIT                                                (1)



//==============================================================================
//              PWM MACROS
//==============================================================================

#define RIGHT_FORWARD_SPEED             (TB3CCR1)
#define LEFT_FORWARD_SPEED              (TB3CCR2)
#define RIGHT_REVERSE_SPEED             (TB3CCR3)
#define LEFT_REVERSE_SPEED              (TB3CCR4)
#define WHEEL_PERIOD                    (100)
#define FULL_SPEED                      (100)
#define HALF_SPEED                      (50)
#define QUARTER_SPEED                   (25)
#define EIGHTH_SPEED                    (17)
#define SIXTEENTH_SPEED                 (2500)
#define WHEEL_OFF                       (0)
#define FULL_SPEED_RIGHT                (90)
#define FULL_SPEED_RIGHT2                (100)
#define FULL_SPEED_LEFT                 (100)
#define HALF_SPEED_RIGHT                (72)
#define HALF_SPEED_LEFT                 (80)
#define QUARTER_SPEED_LEFT              (70)
#define QUARTER_SPEED_RIGHT             (63)
#define NEW_SPEED                       (30)
#define MAKEUP_SPEED                    (80)
#define MAKEUP_SPEED2                   (90)


//==============================================================================
//              ADC MACROS
//==============================================================================

#define NEXT (1)
#define ADD_HEX (0x30)
#define END1 (4)
#define HUNDREDS (100)
#define TENTHS (10)
#define THOUSANDTHS (1000)
#define FIRST (1)
#define SECOND (2)
#define THIRD (3)
#define HUNDREDS_END (99)
#define TENTHS_END (9)
#define THOUSANDTHS_END (999)
#define BEGINNING (0)
#define BLACK (185)
#define FOUR_ELEMENTS (4)
#define START_ELEMENT  (0)
#define FIRST_CHAR_ADC  (0)
#define CHANNEL_A0      (0x000)
#define CHANNEL_A1      (0x001)
#define CHANNEL_A2      (0x002)
#define CHANNEL_A3      (0x003)
#define TENTH_CHAR (9)
#define NINTH_CHAR (8)
#define EIGHTH_CHAR (7)
#define SEVENTH_CHAR (6)
#define SIXTH_CHAR (5)

//==============================================================================
//              PROJECT 7 MACROS
//==============================================================================

#define ONE_DONE                        (1)
#define TWO_DONE                        (2)
#define CALIBRATION_RANGE               (50)
#define HUNDRED_MS                      (1)
#define OVERLINETIME                    (4)
#define TB0CCR2_INTERVAL                (25000) //50msec
#define ONE_SEC_CCR2                    (20)
#define SPEED1                          (35000)
#define ONES_PLACE                      (10)
#define OVERLINETIME2                   (4)
#define OVERLINETIME3                   (6)
#define OVERLINETIME4                   (10)
#define TIMEDONE                        (31)
#define FIRST_ELEMENT                   (0)
#define SECOND_ELEMENT                   (1)
#define THIRD_ELEMENT                   (2)
#define FOURTH_ELEMENT                   (3)

//==============================================================================
//              SERIAL MACROS
//==============================================================================

#define BRW_115200                      (4)
#define MCTLW_115200                    (0x5551)
#define BRW_460800                      (1)
#define MCTLW_460800                    (0x4A11)
#define SMALL_RING_SIZE                 (16)
#define BEGINNING                       (0)
#define LARGE_RING_SIZE                 (16)
#define END_CHAR                        (0x0D)
#define UCA_FLAG_INTERVAL               (0x08)
#define NO_UCA_FLAG                     (0)
#define UCA_RX_FLAG                     (2)
#define UCA_TX_FLAG                     (4)
#define BAUD_115200                     (0)
#define BAUD_460800                     (1)
#define BAUD_9600                       (2)
#define BRW_9600                        (52)
#define MCTLW_9600                      (0x4911)

//==============================================================================
//              PROJECT 8 MACROS
//==============================================================================

#define COMMAND_CHARS					(11)
#define LAST_CHAR_COMMAND				(10)
#define APPEND					        (1)

//==============================================================================
//              PROJECT 9 MACROS
//==============================================================================

#define COMMAND_ARRAY_LENGTH                            (10)
#define LEFT_TURN_TIME                                  (12)
#define RIGHT_TURN_TIME                                 (6)
#define MARKER_CHAR                                     (8)
#define TIMER_BEGIN_CHAR                                (4)
#define TIMER_END_CHAR                                  (8)
#define DOWN_TWO                                        (2)
#define DOWN_THREE                                      (3)
#define DOWN_FOUR                                       (4)