#ifndef CHERRYTREE_H_
#define CHERRYTREE_H_ KIRSCH

#include "task.h"

typedef struct {
    uint32_t pnumber;
    int32_t total_timeunits; // signed integer used to eventually support time travel
    int32_t remaining_timeunits;
    uint16_t resources;
    int16_t priority;
    
    struct ct_task_t * next;
} ct_task_t;

#endif
