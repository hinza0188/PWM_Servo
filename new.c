#include "new.h"
void servo_Init(servo* e, enum Channel channel_id)
{
	e->loop_index =0;
	e->recipe_index =0;
	e->s_loop_index =0;
	e->wait =10;
	e->end_recipe= 0;
	e->pend =0;
	e->present_location =0;
	e->Channel = channel_id;
	}
void operate (servo* e)
{
	if( !end_recipe  && !e->pend )
	{
		if(e->wait !=0)
		{
			e->wait --;
			}
		else
		{
		switch(e->recipe[e->recipe_index] & 0xE0)
		{
		case MOV:
						mov(e,e->recipe[e->recipe_index] & 0x1F);
						break;
		case WAIT :
						wait(e,e->recipe[e->recipe_index] & 0x1F);
						break;
		case LOOP :
						loop(e,e->recipe[e->recipe_index] & 0x1F);
						break;
		case END_LOOP:
						end_loop(e);
						break;
		case RECIPE_END:
						recipe_end_function(e);
						break;
		case JUMP:
						jump(e,e->recipe[e->recipe_index] & 0x1F);
						break;
	}
		e->recipe_index ++;
}
		}
	}

	void mov(servo* e,uint8_t val)
	{
		move(e,val);
			if(val > e->present_location)
			{
				e->wait = 2*(val - e->present_location);
			}
			else 
			{
				e->wait = -2 *(val -e->present_location);
			}
			e->present_location = val;
			
		}
	void wait(servo* e, uint8_t val)
	{
			e->wait = val;
	}
	
	void loop(servo* e, uint8_t val)
	{
			e->s_loop_index = e->recipe_index;
			e-> loop_index = val;
	}
	void end_loop(servo* e)
	{
		if(e->loop_index !=0)
		{
			e->loop_index = e->s_loop_index;
			e->loop_index --;
		}
	}
	void recipe_end_function(servo* e)
	{
			e->recipe_end = 1;
	}
	
///////GRAD PART/////
	void jump(servo* e ,uint8_t val)
	{
		e->recipe_index = val -1;
	}
	
	void move(servo* e,int location)
	{
		if(e->Channel == CHANNEL_1_ID)
		{
			switch(location)
			{
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
	} 
		else 
			{	// represents servo connected to PA1
		switch (location) 
			{
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

		
