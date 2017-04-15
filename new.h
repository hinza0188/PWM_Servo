#include <stm32l476xx.h>
#define MOV (0x20)
#define WAIT (0x40)
#define LOOP (0x80)
#define END_LOOP (0x81)
#define RECIPE_END (0)
#define JUMP (0x30)

enum Channel {
	CHANNEL_1_ID, CHANNEL_2_ID
};

typedef struct servo servo;
struct servo
{
		uint8_t recipe[50];
		int wait;
		int recipe_index;
		int loop_index;
		int s_loop_index;
		int present_location;
		int end_recipe;
		enum Channel Channel;
		int pend;
};

void operate (servo* e);
void recipe_end_function(servo* e);
void servo_Init(servo* e, enum Channel channel_id);
void mov(servo* e, uint8_t val);
void wait(servo* e, uint8_t val);
void loop(servo* e, uint8_t val);
void end_loop(servo* e);
void jump(servo* e, uint8_t val);
void move(servo* e, int location);
