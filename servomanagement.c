
void servo_init(servo* p , 
{
		p->loop_index=0;
	  p->wait_servo=10;
    p->startloop_index=0;
		p->current_postion = 0;
		p->recipe_index=0;
}
	



void servomanagement(servo* p)
{
	if(//recipe paused && recipe ended & recipe pending)
	{
		for(int i=0; i<10; i++);
	}
	else 
	{
		switch(p->recipe[recipe_index]&0xE0)
			case MOV:
				mov(p,p->recipe[recipe_index] & 0x1F);
				break;
			case WAIT:
				wait(p,p->recipe[recipe_index]& 0x1F);
				break;
			case LOOP:
				loop(p,p->recipe[recipe_index] & 0x1F);
				break;
			case END_LOOP:
				endloop(p,p->recipe[recipe_index]);
				break;
			case 
		}	
				
void mov(servo* p, uint8_t param )
{
	setposition(p,param);
	if(param > p->current_position)
 {
		e->wait_servo = 2 * (val - p->current_postion);
	}
	else {
		e->wait_servo = -2 * (val - p->current_postion);
	}
	
	e->current_postion = val;
}

	
			
}
void wait(servo* p, uint8_t param )
{
	p->wait_servo=param;
	
}
void loop(servo* p, uint8_t param)
{
	p->startloop_index= p->recipe_index;
	p->loop_index=;
}
void endloop()
{
	if(p->loop_index!=0)
	{
		p->recipe_index = p->startloop_index;
		p->loop_index--;
}

void setposition(servo* p, param) 
switch(param)
	case 0:
		new_position
	
	