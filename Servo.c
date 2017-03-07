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

//unsigned char recipe1[] = { MOV + 3, MOV | 5, RECIPE_END } ;
unsigned char recipe1[] = { MOV + 0, MOV + 5, MOV + 0, MOV + 4, LOOP + 5, MOV + 1, MOV + 4} ;
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
				TIM2->CCR1 = (7);			// at 36 degree, servo duty is 0.7ms
				break;
			case 2:
				TIM2->CCR1 = (10);		// at 72 degree, servo duty is 1.0ms
				break;
			case 3:
				TIM2->CCR1 = (13);		// at 108 degree, servo duty is 1.3ms
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
				TIM2->CCR2 = (13);		// at 108 degree, servo duty is 1.3ms
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
	//int default_wait = 5;									// wait at least 100 ms 
	int start_count = TIM5->CCR1;					// get current timer count
	int end_count = start_count + 100000;	// get 1 second later
	if (param) {
		end_count = end_count + (100000 * param);
	}
	if (!servo) { // represents servo connected to PA0
		
		
		
	} else { // represents servo connected to PA1
		
		
		
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

void run_recipe(void) {
	return;
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
