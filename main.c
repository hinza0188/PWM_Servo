/*
* Author: Yongki (Jay) / Gowtham
*/
/* include header files */
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Init.h"
#include "Servo.h"
#include "UI.h"
#include "recipe.h"

/* declare variables here */
uint8_t mainBuffer[BufferSize];

int main(void){
	System_Clock_Init();		// Switch System Clock = 80 MHz
	UART2_Init();						// Initialize uart interaction
	GPIO_Init();						// Initialize GPIO pin settings
	PWM_Init();							// Initialize TIM2 PWM Mode
	Counter_Init();					// Initialize TIM5 Counter Mode
	
  
	//operate(32, 0);						// MOV + 0 for the left servo ( PA0 )
	//operate(37, 1);						// MOV + 5 for the right servo ( PA1 )
	
	user_prompt();					// Call user prompt interaction
	while (1) { // run forever
		// check servo 1 is free
		// check servo 2 is free
		// check if user input
		// wait till 1/100 millisecond
	}
	
	
}
