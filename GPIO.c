#include "stm32l476xx.h"
#include "GPIO.h"

/*
* Initialize GPIO Port A and B into Output Mode
*/
void GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 	// Enable GPIO Port A
  GPIOA->MODER &= ~3;                  	// clear MODER Bytes for Port A
	GPIOA->MODER |= 0x1; 									// Set Port A to Output Mode
	//GPIOA->OTYPER &= ~0x10;								// set PA 0 and 1 to be push-pull (reset state) type ?
	//GPIOA->OSPEEDR &= ~0x10;							// set PA 0 and 1 to be low speed ?
	//GPIOA->PUPDR |= 0x2;									// pull down on PA0 ?
	//GPIOA->ODR |= 0x0;										// set PA0 output data register ?
}
