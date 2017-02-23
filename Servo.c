/*
* Author: Yongki An
*/

// Include all required headers
#include "Servo.h"

/* define status of the servo in private variable */
static enum servo_states current_servo_state = state_unknown ;

// Define all of the commands that are valid
#define NULL (0)
#define MOV (0x20)
#define RECIPE_END (0)

// Examples of simple recipes
// Note that, because the bottom 5 bits are zeros adding or bitwise or'ing
// in the values for the bottom 5 bits are equivalent. However, using a bitwise
// or is better at communicating your purpose.
unsigned char recipe1[] = { MOV + 3, MOV | 5, RECIPE_END } ;
unsigned char recipe2[] = { MOV | 5, MOV | 2, RECIPE_END } ;

// If you set up an array like this then you can easily switch recipes
// using an additional user input command.
unsigned char *recipes[] = { recipe1, recipe2, NULL } ;

// Code to start the move (adjust PWM) and start the timing delay based on the
// current position.
static void start_move( enum servo_states new_state ) {
	// TBD
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
