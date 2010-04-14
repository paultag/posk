#ifndef TASK_H_
#define TASK_H_ YUP

#include "common.h"

typedef struct {
    uint32_t tid;
    uint32_t state;
    
    uint32_t esp,ebp,ebx,esi,edi;
} task_t;



#endif