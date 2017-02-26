#include "stm32l476xx.h"
#include "GPIO.h"

/*
* Initialize GPIO Port A and B into Output Mode
*/
void GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 	// Enable GPIO Port A
	GPIOA->MODER &= ~15;									// clear MODER Bytes of PA0 and PA1
	GPIOA->MODER |= 0xA; 									// Set PA0 and PA1 to Alternate Function Mode
	GPIOA->AFR[0] |= 0x1;									// Assign AF 1 Register for TIM 2 connection
	GPIOA->PUPDR |= 0xA;									// Set Pull-Down mode for PA0 and PA1
}

void TIM_Init(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; // Enable Timer 2 Clock
	TIM2->PSC = 79;												// Set 80Mhz CPU Pre-Scalar
	TIM2->CCER &= 0x1;										// Disable Timer 2 output register
	TIM2->CCMR1 &= 0x00;									// Clear CCMR1 CC1S bit to set output mode
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;				// Set OC1PE (output Compare 1 Preload Enable)
	TIM2->CR1 |= TIM_CR1_ARPE;						// Set the Auto-Reload Preload Enable bit
	TIM2->ARR = (20*1000);								// Set Auto Reload Register of 20 milli-seconds period
	TIM2->CCR1 = (380);										// Set the pulse width of 380 micro-seconds in CCR1 Register
	TIM2->EGR |= 0x01;										// Force update by setting EGR bit
	TIM2->CCER |= 0x1;										// Enable Timer 2 output register
}
