/*
* Author: Yongki An
*/

// Include all required headers
#include "stm32l476xx.h"
#include "Servo.h"

// Define all of the commands that are valid
#define NULL (0)
#define MOV (0x20)
#define WAIT (0x40)
#define LOOP (0x80)
#define END_LOOP (0x81)
#define RECIPE_END (0)

/* define status of the servo in private variable */
static enum servo_states current_servo_state = state_unknown ;

// Examples of simple recipes
// Note that, because the bottom 5 bits are zeros adding or bitwise or'ing
// in the values for the bottom 5 bits are equivalent. However, using a bitwise
// or is better at communicating your purpose.
unsigned char recipe1[] = { MOV + 3, MOV | 5, RECIPE_END } ;
unsigned char recipe2[] = { MOV | 5, MOV | 2, RECIPE_END } ;

// If you set up an array like this then you can easily switch recipes
// using an additional user input command.
unsigned char *recipes[] = { recipe1, recipe2, NULL } ;

/*
* Execute each one recipe command
* int dude = Total value of opcode + parameter in decimal form
* int servo = (0 -> PA0, 1 -> PA1)
* returns None
*/
void operate( int dude, int servo ) {
	int opcode = (dude & 224);
	int param = (dude & 31);
	
	switch (opcode) {
		case MOV: 					// opcode is 001
			move(param, servo);
			break;
		case WAIT: 					// opcode is 010
			wait(param, servo);
			break;
		case LOOP: 					// opcode is 100
			loop(param, servo);
			break;
		case END_LOOP: 			// opcode is 101
			end_loop(servo);
			break;
		case RECIPE_END: 		// opcode is 000
			end_recipe(servo);
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
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
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
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				TIM2->CCR2 = (21);		// at 180 degree, servo duty is 2.14ms
				break;
		}
	}
}

void wait(int param, int servo) {
	if (!servo) { // represents servo connected to PA0
		// do functionality here
	} else { // represents servo connected to PA1
		// do functionality here
	}
}

void loop(int param, int servo) {
	if (!servo) { // represents servo connected to PA0
		// do functionality here
	} else { // represents servo connected to PA1
		// do functionality here
	}
}

void end_loop(int servo) {
	if (!servo) { // represents servo connected to PA0
		// do functionality here
	} else { // represents servo connected to PA1
		// do functionality here
	}
}

void end_recipe(int servo) {
	if (!servo) { // represents servo connected to PA0
		// do functionality here
	} else { // represents servo connected to PA1
		// do functionality here
	}
}


static void start_move( enum servo_states my_state ) {
	return;
}




// This section should be in a separate .c file such as state_machine.c.
// In this code you add code to each case to process the 
void process_event(enum events one_event) {
	switch ( current_servo_state ){
		case state_position_0 :		// right-most position
			if ( one_event == user_entered_left ) {
				start_move( state_position_1 ) ;
				current_servo_state = state_moving ;		// when the move ends (enough time has elapsed) new state will be state_position_1
			}
      break ;
		case state_unknown :
			break ;
		case state_recipe_ended :
			break ;
    case state_position_1:
      break;
    case state_moving:
      break;
	}
}
