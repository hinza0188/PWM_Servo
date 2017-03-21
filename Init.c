#include "stm32l476xx.h"
#include "Init.h"

/*
* Initialize GPIO Port A and B into Output Mode
*/
void GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 	// Enable GPIO Port A
	GPIOA->MODER &= ~15;									// clear MODER Bytes of PA0 and PA1
	GPIOA->MODER |= 0xA; 									// Set PA0 and PA1 to Alternate Function Mode
  GPIOA->AFR[0]|= 0x11;								  // Assign AFRL1 (PA0)Register for TIM 2 connection
//  GPIOA->PUPDR |= 0xA;									// Set Pull-Down mode for PA0 and PA1
}

/*
* Initialize TIM2 Channel 1 and 2 into Alternate function mode
* and set it to PWM mode
*/
void PWM_Init(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; // Enable Timer 2 Clock
	TIM2->PSC = 7999;											// Set 80Mhz CPU Pre-Scalar in 100 milli-second
	TIM2->CCER &= 0x1;										// Disable Timer 2 output register
	TIM2->CCMR1 &= 0x00;									// Clear CCMR1 CC1S bit to set output mode
  
  TIM2->CCMR1 |= TIM_CCMR1_OC1M;        // Set OC1M (Output Compare 1 Mode)
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;				// Set OC1PE (output Compare 1 Preload Enable)
  
  TIM2->CCMR1 |= TIM_CCMR1_OC2M;        // Set OC1M (Output Compare 2 Mode)
  TIM2->CCMR1 |= TIM_CCMR1_OC2PE;       // Set OC1PE (output Compare 2 Preload Enable)
  
	TIM2->CR1 |= TIM_CR1_ARPE;						// Set the Auto-Reload Preload Enable bit
	TIM2->ARR = (200);							  	  // Set Auto Reload Register of 20 milli-seconds period
	TIM2->CCR1 = (4);										  // Set the pulse width of 400 micro-seconds in Channel 1
  TIM2->CCR2 = (4);                     // Set the pulse width of 400 micro-seconds in Channel 2
  
	TIM2->CCER |= TIM_CCER_CC1E;					// Enable Timer 2 channel 1
  TIM2->CCER |= TIM_CCER_CC1P;          // Set Polarity in channel 1 for active high
  TIM2->CCER |= TIM_CCER_CC2E;          // Enable Timer 2 channel 2
  TIM2->CCER |= TIM_CCER_CC2P;          // Set Polarity in channel 2 for active high
  
  TIM2->EGR |= 0x01;										// Force update by setting EGR bit
	TIM2->CR1 |= TIM_CR1_CEN; 						// Run the timer for PWM
}


/*
* Initialize TIM5 and checks for the wait count
*/
void Counter_Init(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM5EN;	// Enable Timer 5 Clock
	TIM5->PSC = 7999;											// Set 80Mhz CPU Pre-Scalar in 100 milli-second
	TIM5->CCER &= 0x1;										// Disable Timer 5 output register
	TIM5->CCMR1 |= TIM_CCMR1_OC1M;				// The channel is now output capture mode
	TIM5->CCER |= 0x1;										// Enable Timer 5 output register
	
	TIM5->EGR |= 0x01;										// Force update by setting EGR bit
	TIM5->CR1 |= TIM_CR1_CEN;							// Start the timer
}
