/*
* Author: Yongki (Jay) / Gowtham
*/
/* include provided start up code*/
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

/*include our code */
#include "GPIO.h"
#include "Servo.h"
#include "UI.h"

/* include useful C libraries */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
/* define good numbers */
#define BufferSize 100

/* declare variables here */
uint8_t buffer[BufferSize];

int main(void){
	
	System_Clock_Init();		// Switch System Clock = 80 MHz
	UART2_Init();
	GPIO_Init();
	Servo_Init();
	user_prompt();

	return 0;
}