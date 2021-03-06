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
uint8_t Buffer[BufferSize];
uint32_t* pRx_counter;
int wait_count_0 = 0;
int wait_count_1 = 0;
int global_pause_0 = 1;			// puase all for testing purposes
int global_pause_1 = 1;			// pause al lfor testing purposes


void global_wait() {
	int counter;
	Counter_Init();					// Initialize TIM5 Counter Mode
	while(1){
		counter = TIM5->CNT;
		if ( counter > 0x1800 ) {			// WAIT 100 ms
			TIM5->CR1 &= 0;							// Stop the timer for reseting the counter value
			break;
		}
	}
}

int main(void){

	int i,idx0, idx1;
  //char end_prompt[] = "function has been executed!\r\n";
	char input_prompt[] = "Type two commands for asynchronous Servo running\r\n";
	const char *prompts[PROMPT_SIZE];
	prompts[0] = "Welcome to the Project 2, and here are the instructions\r\n";
	prompts[1] = "1.Press P or p for pausing the execution\r\n";
	prompts[2] = "2.Press C or c to continue the recipe\r\n";
	prompts[3] = "3.Press R or r to move 1 position to the right if possible\r\n";
	prompts[4] = "4.Press L or l Move 1 position to the left if possible\r\n";
	prompts[5] = "5.Press N or n for No-operation\r\n";
	prompts[6] = "6.press B or b to restart the reciepe\r\n";

	System_Clock_Init();		        // Switch System Clock = 80 MHz
	UART2_Init();										// Initialize uart interaction
	NVIC_SetPriority(USART2_IRQn, 0);			// Set Priority to 1
	NVIC_EnableIRQ(USART2_IRQn);					// Enable interrupt of USART2 peripheral
	GPIO_Init();										// Initialize GPIO pin settings
	PWM_Init();											// Initialize TIM2 PWM Mode
	
	USART_IRQHandler(USART2, Buffer, pRx_counter);
	//////////////////////////////PRINT TUTORIAL////////////////////////////////////
	for (i=0; i<PROMPT_SIZE; i++) {
		// print all 6 prompt lines for user tutorial
		USART_Write( USART2, (uint8_t *)prompts[i], strlen(prompts[i]));
	}
	USART_Write( USART2, (uint8_t *)input_prompt, sizeof(input_prompt));
	////////////////////////////////////////////////////////////////////////////////
	for(;;) { // run forever
		///////////////////////////////////////////////////////////////////////////////
		// check if user input
		// parse it here?
		                   
		////////////////////////////////////////////////////////////////////////////////
		// call recipe
		idx0 = 0; 	// the index number of the recipe 1
		idx1 = 0;		// the index number of the recipe 2
		while (recipe1[idx0] != RECIPE_END || recipe2[idx1] != RECIPE_END) { //run until recipe_end found
			//UI goes here?//
			
			/*
			
			USART_Write(USART2, (uint8_t *)newline, sizeof(newline));
			
			for(i=0;i<2;i++) {
				if (i==0) {
					if(rxbyte[i]== 'P' || rxbyte[i] == 'p') {
						global_pause_0 = 1;
					}
					else if(rxbyte[i] == 'C' || rxbyte[i] == 'c') {
						
					}
					else if(rxbyte[i]== 'R' || rxbyte[i] == 'r') {
						
					}
					else if (rxbyte[i]== 'L' || rxbyte[i] == 'l') {
						
					}
					else if (rxbyte[i] == 'N' || rxbyte[i] == 'n') {
						
					}
					else if (rxbyte[i]== 'B' || rxbyte[i] == 'b') {
					
					}
				} else {
					if(rxbyte[i]== 'P' || rxbyte[i] == 'p') {
						global_pause_1 = 1;
					}
					else if(rxbyte[i] == 'C' || rxbyte[i] == 'c') {
						
					}
					else if(rxbyte[i]== 'R' || rxbyte[i] == 'r') {
						
					}
					else if (rxbyte[i]== 'L' || rxbyte[i] == 'l') {
						
					}
					else if (rxbyte[i] == 'N' || rxbyte[i] == 'n') {
						
					}
					else if (rxbyte[i]== 'B' || rxbyte[i] == 'b') {
						
					}
				}
			}
			*/
			
			
			
			
			
			//////////////////////////////////// SERVO 0 ///////////////////////////////////////////////////
			if (!(global_pause_0)) {
				if (wait_count_0 < 1) {
					operate(recipe1, 0, idx0);       //param: the recipe, servo number, and recipe index
				} else {
					wait_count_0--;
				}
				if (wait_count_0 == 0) {
					idx0++;
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////// SERVO 1 //////////////////////////////////////////////////
			if (!(global_pause_1)) {
				if (wait_count_1 < 1) {
					operate(recipe2, 1, idx1);       //param: the recipe, servo number, and recipe index
				} else {
					wait_count_1--;
				}
				if (wait_count_1 == 0) {
					idx1++;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////
			// write general wait for 100 ms using timer 5
			global_wait();
		}
		// recipe calling ends here ///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
	}	
}
