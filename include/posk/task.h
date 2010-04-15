#ifndef TASK_H_
#define TASK_H_ YUP

#include "common.h"

typedef struct {
    uint32_t state;
    uint32_t resources;
    uint32_t esp,ebp,ebx,esi,edi;
    uint32_t tid;                 // task ID
    uint8_t  prior;               // priority
} task_t;

#endif