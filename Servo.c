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

/* define status of the servo in private variable */
static enum servo_states current_servo_state = state_unknown ;

/*
unsigned char recipe1[] = { 
	MOV + 5, MOV + 0, MOV + 5, MOV + 0,  MOV + 5, MOV + 3, LOOP + 2 , RECIPE_END 
};
*/
unsigned char recipe1[] = { 
	MOV, MOV + 1, LOOP + 0, MOV + 5, MOV + 4, END_LOOP, MOV + 2, MOV + 3, MOV + 4, MOV + 5, RECIPE_END 
};
unsigned char recipe2[] = { 
	MOV + 5, MOV + 4, MOV + 3, MOV + 2,  MOV + 1, MOV + 0, RECIPE_END 
};
unsigned char *recipes[] = { recipe1, recipe2, 0 };

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
			loop(param, recipe_idx, recipe);
			break;
		case END_LOOP: 			    // opcode 101
			end_loop(recipe_idx);
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
		
	} else { // represents servo connected to PA1

	}
}

// inserts into subject[] at position pos
void append(unsigned char subject[], const char insert[], int pos) {
    //unsigned char temp[10] = {};
        
        
}

void remove_command(unsigned char recipe[], int i) {
    for (; recipe[i]; i++) {
        recipe[i] = recipe[i+1];
    }
}

// grab the recipe and modify the operate order
void loop(int param, int recipe_idx, unsigned char recipe[]) {
    int i=0;
    //int recipe_len = sizeof(recipe);
    if (param == 0) {
        // kill the looping command in the recipe
        while (recipe[recipe_idx] != (unsigned char)END_LOOP) {
            remove_command(recipe,recipe_idx);
            i++;
        }
        remove_command(recipe,recipe_idx);
        // delete loop and end_loop command and finish the process
        return;
    }
    
    /*
    while(recipe[recipe_idx+i]!=END_LOOP) {
        // create temporary list of commands that are between loop and end_loop
        //const char new_command = recipe1[recipe_idx+i];
        i++;
    }
    */
    
    
    
}

// gives the line recipe index number of the end_loop
int end_loop(int recipe_idx) {
	int start, end;
	start = 1;
	while(recipe1[recipe_idx+start]==END_LOOP) {
		start++;
	}
	end = recipe_idx + start;

	return end;	
}

// Blink the LED here
void end_recipe(int line) {
	
	// functionality coming soon
    
}

void run_recipe(void) {
	return;
}


static void start_move( enum servo_states my_state ) {
	return;
}




// This section should be in a separate .c file such as state_machine.c.
// In this code you add code to each case to process the 
void process_event(enum events event) {
	switch ( current_servo_state ){
		case state_position_0 :		// left-most position
			if ( event == user_entered_left ) {
				current_servo_state = state_position_0;		// when the move ends (enough time has elapsed) new state will be state_position_1
			} else if (event == user_entered_right) {
				start_move(state_position_1);
				current_servo_state = state_moving;
				// wait for one duty cycle
				current_servo_state = state_position_1;
			}
      break ;
		case state_position_1:
      break;
		case state_position_2:
      break;
		case state_position_3:
      break;
		case state_position_4:
      break;
		case state_position_5:		// right-most position
      break;
		case state_unknown :
			break;
		case state_recipe_ended :
			break;
    case state_moving:
      break;
	}
}
