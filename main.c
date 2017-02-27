/*
* Author: Yongki (Jay) / Gowtham
*/
/* include header files */
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "GPIO.h"
#include "Servo.h"
#include "UI.h"


/* declare variables here */
uint8_t mainBuffer[BufferSize];

int main(void){
	System_Clock_Init();		// Switch System Clock = 80 MHz
	UART2_Init();						// Initialize uart interaction
	GPIO_Init();						// Initialize GPIO pin settings
	TIM_Init();							// Initialize PWM Timer
	user_prompt();					// Call user prompt interaction
}
