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
	int i,idx0, idx1, opcode0, param0, opcode1, param1;
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
	for(;;) { // run forever			
		// check servo 0 is free
		
		// check servo 1 is free
		
		
		
		///////////////////////////////////////////////////////////////////////////////
		// check if user input
		// parse it here?
		                                          
		////////////////////////////////////////////////////////////////////////////////
		// call recipe
		idx0 = 0; 	// the index number of the recipe 1
		idx1 = 0;		// the index number of the recipe 2
		while (recipe1[idx0] != RECIPE_END || recipe2[idx1] != RECIPE_END) { //run until recipe_end found
			opcode0 = ((int)recipe1[idx0] & 224);
			param0 = ((int)recipe1[idx0] & 31);
			opcode1 = ((int)recipe2[idx1] & 224);
			param1 = ((int)recipe2[idx1] & 31);
			
			if (!(opcode0==LOOP && param0 ==0)) {
				operate(opcode0, param0, 0, idx0);
			} else {
				idx0 = end_loop(idx0); 
			}
			
			if (!(opcode1==LOOP && param1==0)) {
				operate(opcode1, param1, 1, idx1);
			} else {
				idx1 = end_loop(idx1);
			}
			
			// write general wait for 100 ms using timer 5
			Counter_Init();					// Initialize TIM5 Counter Mode
			while(1){
				counter = TIM5->CNT;
				if ( counter > 0x2000 ) {			// WAIT 100 ms
					TIM5->CR1 &= 0;							// Stop the timer for reseting the counter value
					break;
				}
			}
			idx0++;
			idx1++;
		}
		operate(RECIPE_END, 0, 0, 0);
		// recipe calling ends here ///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
	}	
}
