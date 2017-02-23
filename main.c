/*
* Author: Yongki (Jay) / Gowtham
*/
/* include provided start up code*/
#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"

/*include our code */
#include "GPIO.h"
#include "Servo.h"
#include "UI.h"


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
