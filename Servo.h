/*
* Author: Yongki An
*/

// This is a good way to define the status of the display.
// This should be in a header (.h) file.
enum status {
	status_running,
	status_paused,
	status_command_error,
	status_nested_error 
};

// This is a good way to define the state of a servo motor.
// This should be in a header (.h) file.
enum servo_states {
	state_position_0,
	state_position_1,
	state_unknown,
	state_moving,
	state_recipe_ended
};

// This is a good way to define the event transitions between states.
// This also should be in a header (.h) file.
// More events are needed.
enum events {
	user_entered_left,
	user_entered_right,
	user_entered_pause,
	user_entered_continue,
	user_entered_noop,
	user_entered_restart,
	recipe_ended
};

void end_recipe(int);
void end_loop(int);
void loop(int,int);
void wait(int,int);
void move(int,int);
void operate(int, int);
void process_event(enum events);
