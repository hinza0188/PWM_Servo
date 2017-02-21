#include "stm32l476xx.h"
#include "GPIO.h"

/*
* Initialize GPIO Port A into Alternate Function Mode
*/
void GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // Enable GPIO Port A
  GPIOA->MODER &= ~3;                  // clear MODER Bytes
	GPIOA->MODER |= 0x2; 								// Set Port A to Alternate Function Mode
	GPIOA->AFR[0] |= 0x1;								// Assign AF 1 Register for timer 2 connection
	//GPIOA->PUPDR |= 0x2;									// Don't know what this does yet
}
