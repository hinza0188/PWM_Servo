#include "recipe.h"`

void recipe_1(smanage* e)
{
	e->recipe[1]=MOV+5;
	e->recipe[2]=MOV+0 ; There must NOT be intervening instructions in this group to allow
  e->recipe[3]=MOV+5 ; verification of default time delay.
	e->recipe[4]=MOV+0;
  e->recipe[5]=MOV+3;
	e->recipe[6]=LOOP+0; Test the default loop behavior.
	e->recipe[7]=MOV+1;
	e->recipe[8]=MOV+4;
	e->recipe[9]=END_LOOP;
	e->recipe[10]=MOV+0;0
	e->recipe[11]=MOV+2;
	e->recipe[12]=WAIT+0;
	e->recipe[13]=MOV+3 ; Move to an adjacent position to verify
	e->recipe[14]=WAIT+0;
	e->recipe[15]=MOV+2;
	e->recipe[16]=MOV+3 ; Measure the timing precision of the 9.3 second delay with an external	
	e->recipe[17]=WAIT+31 ; timer.
	e->recipe[18]=WAIT+31;
	e->recipe[19]=WAIT+31;
	e->recipe[20]=MOV+4;
}
void recipe_2(smanage* e)
{
	e->recipe[1]=MOV+5;
	e->recipe[2]=MOV+0 ; 
  e->recipe[3]=MOV+5 ; 
	e->recipe[4]=MOV+0;
  e->recipe[5]=MOV+3;
	e->recipe[6]=LOOP+0; 
	e->recipe[7]=MOV+1;
	e->recipe[8]=MOV+4;
	e->recipe[9]=END_LOOP;
	e->recipe[10]=MOV+0;
	e->recipe[11]=MOV+2;
	e->recipe[12]=WAIT+0;
	e->recipe[13]=MOV+3 ; 
	e->recipe[14]=WAIT+0;
	e->recipe[15]=MOV+2;
	e->recipe[16]=MOV+3 ; 	
	e->recipe[17]=WAIT+31 ; 
	e->recipe[18]=WAIT+31;
	e->recipe[19]=WAIT+31;
	e->recipe[20]=MOV+4;
}
	

	
