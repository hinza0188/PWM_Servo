/*
* Author: Gowtham Ramakrishnan
*/

#include "stm32l476xx.h"
#include "UART.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PROMPT_SIZE 7

// uint8_t buffer[BufferSize]; //(already declared in main.c) 
uint8_t uiBuffer[BufferSize];

void user_prompt() {			
	// start writing user command code here
	int pause_flag, continue_flag, right_flag, left_flag , noop_flag, reset_flag, i;
	char rxbyte[2];
	const char *prompts[PROMPT_SIZE];
  const char newline[] = "\r\n";
  char end_prompt[] = "function has been executed!\r\n";
	prompts[0] = "Welcome to the Project 2, and here are the instructions\r\n";
	prompts[1] = "1.Press P or p for pausing the execution\r\n";
	prompts[2] = "2.Press C or c to continue the recipe\r\n";
	prompts[3] = "3.Press R or r to move 1 position to the right if possible\r\n";
	prompts[4] = "4.Press L or l Move 1 position to the left if possible\r\n";
	prompts[5] = "5.Press N or n for No-operation\r\n";
	prompts[6] = "6.press B or b to restart the reciepe\r\n";
	
	for (i=0; i<PROMPT_SIZE; i++) {
		// print all 6 prompt lines for user tutorial
		USART_Write( USART2, (uint8_t *)prompts[i], strlen(prompts[i]));
	}
	
	while(1) { // run forever
		char the_prompt[] = "\r\nType two commands for asynchronous Servo running\r\n";
		USART_Write( USART2, (uint8_t *)the_prompt, sizeof(the_prompt));
		
		for(i=0;i<2;i++) {
			// first, run double UART read wait
			rxbyte[i]=USART_Read(USART2);
		}
		strcat(rxbyte, "\r\n"); //add line break to the rxbyte
		// then print the data in the rxbyte
		USART_Write(USART2, (uint8_t *)rxbyte, sizeof(rxbyte));
		USART_Write(USART2, (uint8_t *)newline, sizeof(newline));
		// then run commands
		for(i=0;i<2;i++) {
			if (i==0) {
				if(rxbyte[i]== 'P' || rxbyte[i] == 'p') {
					servo0L_event = user_entered_pause;
				}
				else if(rxbyte[i] == 'C' || rxbyte[i] == 'c') {
					servo0L_event = user_entered_continue;
				}
				else if(rxbyte[i]== 'R' || rxbyte[i] == 'r') {
					servo0L_event = user_entered_right;
				}
				else if (rxbyte[i]== 'L' || rxbyte[i] == 'l') {
					servo0L_event = user_entered_left;
				}
				else if (rxbyte[i] == 'N' || rxbyte[i] == 'n') {
					servo0L_event = user_entered_noop;
				}
				else if (rxbyte[i]== 'B' || rxbyte[i] == 'b') {
					servo0L_event = user_entered_restart;
				}
			} else {
				if(rxbyte[i]== 'P' || rxbyte[i] == 'p') {
					servo1R_event = user_entered_pause;
				}
				else if(rxbyte[i] == 'C' || rxbyte[i] == 'c') {
					servo1R_event = user_entered_continue;
				}
				else if(rxbyte[i]== 'R' || rxbyte[i] == 'r') {
					servo1R_event = user_entered_right;
				}
				else if (rxbyte[i]== 'L' || rxbyte[i] == 'l') {
					servo1R_event = user_entered_left;
				}
				else if (rxbyte[i] == 'N' || rxbyte[i] == 'n') {
					servo1R_event = user_entered_noop;
				}
				else if (rxbyte[i]== 'B' || rxbyte[i] == 'b') {
					servo1R_event = user_entered_restart;
				}
			}
		}
		
		
		USART_Write(USART2, (uint8_t *)end_prompt, sizeof(end_prompt));
	}
}
