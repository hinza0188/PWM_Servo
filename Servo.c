/*
* Author: Yongki An
*/

// Include all required headers
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stm32l476xx.h"
#include "Servo.h"
#include "Init.h"
#include "LED.h"

/*
unsigned char recipe1[] = { 
	MOV + 5, MOV + 0, MOV + 5, MOV + 0,  MOV + 5, MOV + 3, LOOP + 2 , RECIPE_END 
};
*/
unsigned char recipe1[] = { 
	LOOP + 3, MOV + 2, MOV + 3, END_LOOP, WAIT + 31, RECIPE_END 
};
unsigned char space_holder[] = { 
	RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END,
	RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END, RECIPE_END
};
unsigned char recipe2[] = { 
	MOV + 5, MOV + 4, MOV + 3, MOV + 2,  MOV + 1, MOV + 0, WAIT + 31, RECIPE_END 
};
unsigned char *recipes[] = { recipe1, space_holder, recipe2, RECIPE_END };

// Examples of simple recipes
// Note that, because the bottom 5 bits are zeros adding or bitwise or'ing
// in the values for the bottom 5 bits are equivalent. However, using a bitwise
// or is better at communicating your purpose.

/*
* Execute each one recipe command
* int dude = Total value of opcode + parameter in decimal form
* int servo = (0 -> PA0, 1 -> PA1)
* returns None
*/
void operate( unsigned char recipe[], int servo, int recipe_idx ) {
    int opcode = recipe[recipe_idx]&224;
    int param = recipe[recipe_idx]&31;
    
    switch (opcode) {
		case MOV: 					// opcode 001
			move(param, servo);
			break;
		case WAIT: 					// opcode 010
			wait(param, servo);
			break;
		case LOOP: 					// opcode 100
			loop(param, recipe_idx, servo, recipe);
			break;
		case RECIPE_END: 		    // opcode 000
			end_recipe(recipe_idx);
			break;
	}
}

void move(int param, int servo) {
	if (!servo) { // represents servo connected to PA0
		switch (param) {
			case 0:
				TIM2->CCR1 = (4);			// at 0 degree, servo duty is 0.388ms
				break;
			case 1:
				TIM2->CCR1 = (7);			// at 36 degree, servo duty is 0.7ms
				break;
			case 2:
				TIM2->CCR1 = (10);		// at 72 degree, servo duty is 1.0ms
				break;
			case 3:
				TIM2->CCR1 = (14);		// at 108 degree, servo duty is 1.4ms
				break;
			case 4:
				TIM2->CCR1 = (17);		// at 144 degree, servo duty is 1.7ms
				break;
			case 5:
				TIM2->CCR1 = (21);		// at 180 degree, servo duty is 2.14ms
				break;
		}
	} else {	// represents servo connected to PA1
		switch (param) {
			case 0:
				TIM2->CCR2 = (4);			// at 0 degree, servo duty is 0.388ms
				break;
			case 1:
				TIM2->CCR2 = (7);			// at 36 degree, servo duty is 0.7ms
				break;
			case 2:
				TIM2->CCR2 = (10);		// at 72 degree, servo duty is 1.0ms
				break;
			case 3:
				TIM2->CCR2 = (14);		// at 108 degree, servo duty is 1.4ms
				break;
			case 4:
				TIM2->CCR2 = (17);		// at 144 degree, servo duty is 1.7ms
				break;
			case 5:
				TIM2->CCR2 = (21);		// at 180 degree, servo duty is 2.14ms
				break;
		}
	}
}

/*
* Waits at least 100 milli-second, or takes parameter to wait extra time
* (int) param : extra value that takes up to 31 milli seccond (5 bit)
* (int) servo : 0 -> PA0 || 1 -> PA1
*/
void wait(int param, int servo) {
	if (!servo) { // represents servo connected to PA0
		wait_count_0 += param;
	} else { // represents servo connected to PA1
		wait_count_1 += param;
	}
}

// remove recipe command by continuously overriding with next value 
void remove_command(unsigned char recipe[], int i) {
    for (; recipe[i]; i++) {
        recipe[i] = recipe[i+1];
    }
}

// inserts one recipe command into subject[] at position pos
void append(unsigned char recipe[], unsigned char insert[], int pos) {
		int i;
		char *precipe, *pinsert;
		unsigned char temp[100] = {0};		// takes original subject array into temp variable
		precipe = recipe;
		pinsert = insert;
		
		strncpy(temp, precipe, pos);			// copy the first part of the subject into the temp variable
		temp[pos] = '\0';									// terminate the string
		strcat(temp,pinsert);							// concatenate the rest of the insert
		strcat(temp,precipe+pos);				// concatenate the left over subject
		
		// synchronize recipe before temp gets dumped
		for (i=0; temp[i] != '\0'; i++ ) {
			recipe[i] = temp[i];
		}
		
}

// grab the recipe and modify the operate order
void loop(int param, int recipe_idx, int servo, unsigned char recipe[]) {
    int i=0;
		unsigned char temp[20]; 	// reserve 10 space for original looping commands if applicable
    //int recipe_len = sizeof(recipe);
    if (param == 0) { // case 1: remove all recipe command within the loop
        // kill the looping command in the recipe
        while (recipe[recipe_idx] != (unsigned char)END_LOOP) {
            remove_command(recipe,recipe_idx);
            i++;
        }
        remove_command(recipe,recipe_idx);
        // delete loop and end_loop command and finish the process
    } else {	// case 2: param is greater than 1, remove loop and end_loop only and move on
			// copy the repeated part here
			remove_command(recipe,recipe_idx);		// remove loop command
			while(recipe[recipe_idx+i]!=END_LOOP) {
				// create temporary list of commands that are between loop and end_loop
				temp[i] = recipe[recipe_idx+i];
				// const char new_command = recipe1[recipe_idx+i];
				i++;
			}
			remove_command(recipe,recipe_idx+i);	// remove end_loop command
			if (param == 1) { // case 3: param is 1, let modified recipe just run
				operate(recipe, servo, recipe_idx);
				return;
			}
			// case 4: param is more than 2, paste the temp commands
			for (i=0; i < param; i++) { 
				// append the looping commands here
				append(recipe,temp,recipe_idx);
			}
    }
		operate(recipe, servo, recipe_idx);
		return;
}

// Blink the LED here
void end_recipe(int line) {
	
	// functionality coming soon, flip the LED off
  return;
}

void run_recipe(void) {
	return;
}

