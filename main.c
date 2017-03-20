/*
* Author: Yongki (Jay) / Gowtham
*/
/* include header files */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Init.h"
#include "Servo.h"
#include "recipe.h"

#define MOV (0x20)
#define WAIT (0x40)
#define LOOP (0x80)
#define END_LOOP (0x81)
#define RECIPE_END (0)
#define PROMPT_SIZE 7


/* declare variables here */
uint8_t mainBuffer[BufferSize];
enum status servo0L_status, servo1R_status;
enum events servo0L_event, servo1R_event;
enum servo_states servo0L_state, servo1R_state;

int main(void){
	int i;
	char rxbyte[2];
  char end_prompt[] = "function has been executed!\r\n";
	char input_prompt[] = "Type two commands for asynchronous Servo running\r\n";
	const char *prompts[PROMPT_SIZE];
	prompts[0] = "Welcome to the Project 2, and here are the instructions\r\n";
	prompts[1] = "1.Press P or p for pausing the execution\r\n";
	prompts[2] = "2.Press C or c to continue the recipe\r\n";
	prompts[3] = "3.Press R or r to move 1 position to the right if possible\r\n";
	prompts[4] = "4.Press L or l Move 1 position to the left if possible\r\n";
	prompts[5] = "5.Press N or n for No-operation\r\n";
	prompts[6] = "6.press B or b to restart the reciepe\r\n";
	
	System_Clock_Init();		// Switch System Clock = 80 MHz
	UART2_Init();						// Initialize uart interaction
	GPIO_Init();						// Initialize GPIO pin settings
	PWM_Init();							// Initialize TIM2 PWM Mode
	Counter_Init();					// Initialize TIM5 Counter Mode
	
  servo0L_status = status_paused;	
	servo0L_state = state_unknown;
	servo1R_status = status_paused;
	servo1R_state = state_unknown;	
	
	//////////////////////////////PRINT TUTORIAL////////////////////////////////////
	for (i=0; i<PROMPT_SIZE; i++) {
		// print all 6 prompt lines for user tutorial
		USART_Write( USART2, (uint8_t *)prompts[i], strlen(prompts[i]));
	}
	USART_Write( USART2, (uint8_t *)input_prompt, sizeof(input_prompt));
	////////////////////////////////////////////////////////////////////////////////
	while (1) { // run forever			
		// check servo 0 is free
		
		// check servo 1 is free
		
		
		
		///////////////////////////////////////////////////////////////////////////////
		// check if user input
		// parse it here?
		
		////////////////////////////////////////////////////////////////////////////////
		operate(MOV+5, 0);      // MOV + 0 for the left servo ( PA0 )
		operate(MOV+0, 1);			// MOV + 5 for the right servo ( PA1 )		

		
		operate(WAIT,0);	// wait 100 millisecond for PA0 Servo
		operate(WAIT,1);	// wait 100 millisecond for PA1 Servo
	}
	
	
}
