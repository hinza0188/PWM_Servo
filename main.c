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
  
  TIM2->CR1 |= TIM_CR1_CEN; // run the timer for PWM
  
	user_prompt();					// Call user prompt interaction
	
	TIM2->CR1 |= 0x0;				// terminate timer running
	
}
