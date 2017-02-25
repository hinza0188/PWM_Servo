/*
* Author: Gowtham Ramakrishnan
*/

#include "stm32l476xx.h"
#include "UART.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// uint8_t buffer[BufferSize]; //(already declared in main.c) 
uint8_t uiBuffer[BufferSize];

 void pause_servo(int *pause_flag)
			{
					//pause servo commands here
			}
	void continue_servo( int *continue_flag)
	{
		/// continue servo commands here
	}
	
 void right_servo(int *right_flag)
			{
					//pause servo commands here
			}
	void left_servo( int *left_flag)
	{
		/// continue servo commands here
	}
void 	noop_servo(int *noop_flag)
			{
					//pause servo commands here
			}
	void reset_servo( int *reset_flag)
	{
		/// continue servo commands here
	} 	
void user_prompt() {			
	// start writing user command code here
	int pause_flag, continue_flag, right_flag, left_flag , noop_flag, reset_flag ;
	int i;
	char rxbyte[2];
	char prompt[] = "\r\n 1. Press P or p for pausing the execution \r\n 2. Press C or c to continue the recipe \r\n 3. Press R or r to move 1 position to the right if possible\r\n 4. Press L or l Move 1 position to the left if possible 5. Press N or n for No-op\r\n 6. press B or b to restart the reciepe\r\n";
	
	int n= sprintf((char*)uiBuffer, prompt, strlen(prompt));
	USART_Write( USART2,uiBuffer,n);
		
	for(i=0;i<2;i++) 
	{
			rxbyte[i]=USART_Read(USART2);
			if(rxbyte[i]== 'P' || rxbyte[i] == 'p')
			{
				pause_flag=1;
				  pause_servo(&pause_flag );
			}
			else if(rxbyte[i] == 'C' || rxbyte[i] == 'c')
			{
					continue_flag=1;
					continue_servo(&continue_flag);
			
			}
			else if(rxbyte[i]== 'R' || rxbyte[i] == 'r')
			{
					right_flag =1;
					right_servo(&right_flag);
			}
			else if (rxbyte[i]== 'L' || rxbyte[i] == 'l')
			{
					left_flag=1;
					left_servo(&left_flag );
				
			}
			else if (rxbyte[i] == 'N' || rxbyte[i] == 'n')
			{
					noop_flag=1;
					noop_servo(&noop_flag);
			}
			else if (rxbyte[i]== 'B' || rxbyte[i] == 'b')
			{
					reset_flag=1;
					reset_servo(&reset_flag);
			}
		return;
	}
}
