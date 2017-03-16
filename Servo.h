/*
* Author: Yongki An
*/

/* This is a good way to define the status of the display */
enum status {
	status_running,
	status_paused,
	status_command_error,
	status_nested_error 
};

/* This is a good way to define the state of a servo motor */
enum servo_states {
	state_position_0,		// the left most position
	state_position_1,
	state_position_2,
	state_position_3,
	state_position_4,
	state_position_5,		// the right most position
	state_unknown,
	state_moving,
	state_recipe_ended
};

/* This is a good way to define the event transitions between states */
enum events {
	user_entered_left,
	user_entered_right,
	user_entered_pause,
	user_entered_continue,
	user_entered_noop,
	user_entered_restart,
	recipe_ended
};

void run_recipe(void);
void end_recipe(int);
void end_loop(int);
void loop(int,int);
void wait(int,int);
void move(int,int);
void operate(int, int);
void process_event(enum events);
