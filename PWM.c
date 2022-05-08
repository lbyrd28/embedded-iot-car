//------------------------------------------------------------------------------
//  Filename: PWM.c
//
//  Description: This file features all the motor control functions using PWM.
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


//===========================================================================================
//===========================================================================================

//Turn off all the motors (stop)
void fullStop (void) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
}

//Go forward
void forward (unsigned int speed) {
  //RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  RIGHT_FORWARD_SPEED = speed; // P6.0 Right Forward PWM ON amount
  //LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  LEFT_FORWARD_SPEED = speed; // P6.1 Left Forward PWM ON amount
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
}

//left turn going forward
void leftForward (unsigned int speed) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  RIGHT_FORWARD_SPEED = speed; // P6.0 Right Forward PWM ON amount
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
}

//right turn going forward
void rightForward (unsigned int speed) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  LEFT_FORWARD_SPEED = speed; // P6.1 Left Forward PWM ON amount
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
}

//Go reverse full speed
void reverse (unsigned int speed) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
  RIGHT_REVERSE_SPEED = speed; // P6.2 Right Reverse PWM ON amount
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
  LEFT_REVERSE_SPEED = speed; // P6.3 Left Reverse PWM ON amount
}

void clockwise (unsigned int speed) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  LEFT_FORWARD_SPEED = speed; // P6.1 Left Forward PWM OFF
  RIGHT_REVERSE_SPEED = speed; // P6.2 Right Reverse PWM OF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
}

void c_clockwise (unsigned int speed) {
  RIGHT_FORWARD_SPEED = speed; // P6.0 Right Forward PWM OFF
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OF
  LEFT_REVERSE_SPEED = speed; // P6.3 Left Reverse PWM OFF
}

void merge_right(void) {
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM OFF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM on amount
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P3.5 Left Forward PWM OFF
  LEFT_FORWARD_SPEED = FULL_SPEED_LEFT; // P3.5 Left Forward PWM on amount
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM on amount
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P3.7 Right Forward PWM OFF
  RIGHT_FORWARD_SPEED = QUARTER_SPEED_RIGHT; // P3.7 Right Forward PWM on amount
}

void merge_left(void) {
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM OFF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM on amount
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P3.5 Left Forward PWM OFF
  LEFT_FORWARD_SPEED = QUARTER_SPEED_LEFT; // P3.5 Left Forward PWM on amount
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM on amount
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P3.7 Right Forward PWM OFF
  RIGHT_FORWARD_SPEED = FULL_SPEED_RIGHT; // P3.7 Right Forward PWM on amount
}

void merge_right_hard(void){
    LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM OFF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM on amount
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P3.5 Left Forward PWM OFF
  LEFT_FORWARD_SPEED = FULL_SPEED_LEFT; // P3.5 Left Forward PWM on amount
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM on amount
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P3.7 Right Forward PWM OFF
  RIGHT_FORWARD_SPEED = NEW_SPEED; // P3.7 Right Forward PWM on amount
}

void forwardTest(void) {
    RIGHT_FORWARD_SPEED = HALF_SPEED_RIGHT; // P6.0 Right Forward PWM OFF
  LEFT_FORWARD_SPEED = HALF_SPEED_LEFT; // P6.1 Left Forward PWM OFF
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OF
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
}