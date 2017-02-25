#include "stm32l476xx.h"
#include "GPIO.h"

/*
* Initialize GPIO Port A and B into Output Mode
*/
void GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 	// Enable GPIO Port A
  GPIOA->MODER &= ~3;                   // clear MODER Bytes
	GPIOA->MODER |= 0x2; 									// Set Port A to Alternate Function Mode
	GPIOA->AFR[0] |= 0x1;									// Assign AF 1 Register for timer 2 connection
	GPIOA->PUPDR |= 0x2;									// 
}

void TIM_Init(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; // Enable Timer 2 Clock
	TIM2->PSC = 79;												// Set 80Mhz CPU Pre-Scalar
	TIM2->EGR |= 0x01;										// Force update by setting EGR bit
	TIM2->CCER &= 0x1;										// Disable Timer 2 output register
	
	TIM2->CCMR1 &= 0x0;										// The channel is now output
	//TIM2[TIM_CCMR1_CC1S] = 0;						// The channel is now output
	TIM2->CCMR1  |= 0x100;								// Set OC1PE (Output compare 1 preload enable)
	//TIM2->[TIM_CCMR1_OC1PE] = 1;				// Set OC1PE (output Compare 1 Preload Enable)
	TIM2->CR1 |= TIM_CR1_ARPE;						// Set the Auto-Reload Preload Enable bit
	// or TIM2->CR1 |= 0x10000000;				// Set the Auto-Reload Preload Enable bit
	
	TIM2->CCER |= 0x1;										// Enable Timer 2 output register
	TIM2->EGR |= 0x01;										// Force update by setting EGR bit
	
	TIM2->ARR = (20*1000);								// Set Auto Reload Register of 20 milli-seconds period
	TIM2->CCR1 = (0.38*1000);						// Set the pulse width of 380 micro-seconds in CCR1 Register
	TIM2->EGR |= 0x01;										// Force update by setting EGR bit
	
}
