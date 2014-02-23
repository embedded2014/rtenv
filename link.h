
extern unsigned int user_program_start;
extern unsigned int user_program_end;


#define __USER_PROGRAM __attribute((section(".user_program")))
