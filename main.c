#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include "task.h"

void task2()
{

	int i;
	for (i = 0; i < 10; i++){
		printf("task2:%c\n",'0'+i);
		_delay_ms(50);
	}
	printf("task2 has done\n");

	return;
}

void task1()
{
	int i;
	for (i = 0; i < 20; i++){
		printf("task1:%c\n",'a'+i);
		_delay_ms(50);
	}
	printf("task1 has done\n");
	return ;
}

void main()
{
	taskCreate(task1);
	taskCreate(task2);
	startTaskSchedule();
}
