#ifndef __TASK_H_
#define __TASK_H_

#define MAXTASK		8
#define STACKSIZE	100
#define SYSTICK		15

enum STATE{STOPED,RUNNING};

struct  __attribute__ ((__packed__)) context
{
    uint8_t registers[32];
    uint8_t sreg;
    void *stack_pointer;
    uint16_t stack_space;
    void (*Start)(void);
    enum STATE state;
};

int taskCreate(void (*task)(void));

void startTaskSchedule();


#endif
