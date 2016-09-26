#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "usart.h"
#include "timer.h"
#include "hardware.h"
#include "task.h"

uint8_t currentThreadID = 0;
uint8_t taskID = 1;
struct context *context;


void taskKill(){
	context->state = STOPED;
	while(1);
}

void taskIDLE(){
	while(1){
		printf("in IDLE\n");
		_delay_ms(50);
	};
}
struct context SavedContext[MAXTASK] = {
	{
		{0},
		0,
		NULL, STACKSIZE,
		taskIDLE,RUNNING
	},/* first task:IDLE */
};

int taskCreate(void (*task)(void)){
	if (taskID == MAXTASK)
		return 1;
	SavedContext[taskID].Start = task;
	SavedContext[taskID].state = RUNNING;
	SavedContext[taskID].stack_space = STACKSIZE;
	taskID++;

	return 0;
}

ISR(TIMER1_COMPA_vect, ISR_NAKED){

	CONTEXT_SAVE();
    	// clear R1; avr-gcc assumes R1 to be zero when executing C code
    	asm("CLR R1");
    	// do the actual context switch
    	do {
		if (++currentThreadID >= sizeof(SavedContext) / sizeof(SavedContext[0]))
			currentThreadID = 0;
    	} while (SavedContext[currentThreadID].state != RUNNING);

    	context = &SavedContext[currentThreadID];
    	CONTEXT_RESTROE();
    	CONTEXT_RETURN();

}



void startTaskSchedule()
{
    	int i;
    	uint16_t *ptr;
    	uint16_t sp = SPH<<8 | SPL; // TODO: init
    	for (i = 0; i < sizeof(SavedContext)/sizeof(SavedContext[0]); i++)
    	{
        	SavedContext[i].stack_pointer = (void*)sp;
        	ptr = (uint16_t*)(((uint16_t)SavedContext[i].stack_pointer) +1);
        	uint16_t val = (uint16_t)SavedContext[i].Start;
        	val = val << 8 | ((val >> 8) & 0xFF);
        	memcpy(ptr, &val, sizeof(val));
		ptr++;
        	val = (uint16_t)taskKill;
        	val = val << 8 | ((val >> 8) & 0xFF);
        	memcpy(ptr, &val, sizeof(val));
        	sp -= SavedContext[i].stack_space;
    	}

	// setup usart and systick
    	UsartConfig();
    	Timer1Config(SYSTICK);

    	context = &SavedContext[0];
	
    	SavedContext[0].Start();// run the first task
    
    	while(1);
}
