/*
* Author: Yongki An
*/

#define MOV (0x20)
#define WAIT (0x40)
#define LOOP (0x80)
#define END_LOOP (0x81)
#define RECIPE_END (0)

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

extern unsigned char recipe1[];
extern unsigned char recipe2[];
extern unsigned char *recipes[];

void run_recipe(void);
void end_recipe(int);
int end_loop(int);
void remove_command(unsigned char[], int);
void append(unsigned char[], const char[], int);
void loop(int,int,unsigned char[]);
void wait(int,int);
void move(int,int);
void operate(unsigned char[],int,int);
void process_event(enum events);
