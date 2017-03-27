/*
* Author: Yongki An
*/

#define MOV (0x20)
#define WAIT (0x40)
#define LOOP (0x80)
#define END_LOOP (0x81)
#define RECIPE_END (0)

extern unsigned char recipe1[];
extern unsigned char recipe2[];
extern unsigned char *recipes[];
extern int wait_count_0;
extern int wait_count_1;
extern int global_puase_0;
extern int global_pause_1;

void run_recipe(void);
void end_recipe(int);
void remove_command(unsigned char[], int);
void append(unsigned char[], unsigned char[], int);
void loop(int,int,int,unsigned char[]);
void wait(int,int);
void move(int,int);
void operate(unsigned char[],int,int);
