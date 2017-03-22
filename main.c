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


/* declare variables here */
uint8_t mainBuffer[BufferSize];
enum status servo0L_status, servo1R_status;
enum events servo0L_event, servo1R_event;
enum servo_states servo0L_state, servo1R_state;

int wait_counter_0, wait_counter_1 = 0;

//unsigned char recipe1[] = { MOV + 0, WAIT + 2, MOV + 5, MOV + 0, MOV + 5,  MOV + 0, MOV + 5 } ;
//unsigned char recipe2[] = { MOV + 0, MOV + 1, MOV + 2, MOV + 3,  MOV + 4, WAIT + 2, MOV + 5 } ;
//unsigned char *recipes[] = { recipe1, recipe2, NULL } ;

int main(void){
	int i,j;
	int counter;
	int *recipe1 = calloc(RECIPE_SIZE, sizeof(int));
	int *recipe2 = calloc(RECIPE_SIZE, sizeof(int));
//	 char rxbyte[2];
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
	//fill these up  //////////////////////////////////////////////////////////////
	recipe1[0] = MOV+5;
	recipe1[2] = MOV+0;
	recipe1[3] = MOV+5;
	recipe1[4] = MOV+0;
	////////////////////////////////////////////////////////////////////////////////
	recipe2[0] = MOV+1;
	recipe2[1] = MOV+2;
	recipe2[2] = MOV+3;
	recipe2[4] = MOV+4;
	// until this point ///////////////////////////////////////////////////////////////
	
	
	
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
		for (j=0; j<RECIPE_SIZE; j++) {
			operate((int)recipe1[j], 0);\
			operate((int)recipe2[j], 1);
			
			// write general wait for 100 ms using timer 5
			Counter_Init();					// Initialize TIM5 Counter Mode
			while(1){
				counter = TIM5->CNT;
				if ( counter > 0xA00 ) {			// WAIT 100 ms
					TIM5->CR1 &= 0;							// Stop the timer for reseting the counter value
					break;
				}
			}
		}	// recipe calling ends here ///////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
	}
	
	
}
