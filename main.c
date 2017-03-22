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

#define PROMPT_SIZE 7

/* declare variables here */
uint8_t mainBuffer[BufferSize];
enum status servo0L_status, servo1R_status;
enum events servo0L_event, servo1R_event;
enum servo_states servo0L_state, servo1R_state;

int main(void){
	int i,j;
	int counter;
//	char rxbyte[2];
//  char end_prompt[] = "function has been executed!\r\n";
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
		// call recipe
		j = 0; 	// the index number of the recipe
		while (recipe1[j] != RECIPE_END || recipe2[j] != RECIPE_END) {
			operate((int)recipe1[j], 0, j);
			operate((int)recipe2[j], 1, j);
			
			// write general wait for 100 ms using timer 5
			Counter_Init();					// Initialize TIM5 Counter Mode
			while(1){
				counter = TIM5->CNT;
				if ( counter > 0x2000 ) {			// WAIT 100 ms
					TIM5->CR1 &= 0;							// Stop the timer for reseting the counter value
					break;
				}
			}
			j++;
		}	// recipe calling ends here ///////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
	}
	
	
}
