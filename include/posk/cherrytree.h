#ifndef CHERRYTREE_H_
#define CHERRYTREE_H_ KIRSCH

#include "task.h"

typedef struct {
    uint32_t pnumber;
    int32_t total_timeunits; // signed integer used to eventually support time travel
    int32_t remaining_timeunits;
    uint16_t resources;
    uint16_t priority;
    uint32_t start_time;
    int32_t end_time;
    uint8_t shown;
    
    struct ct_task_t * next;
} ct_task_t;

void doNothing(uint32_t timeunits, uint32_t pnumber);
uint8_t moreTasks();
void print_sched_stats();

#endif
