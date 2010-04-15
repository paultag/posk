#ifndef TASK_H_
#define TASK_H_ YUP

#include "common.h"

typedef struct {
    uint32_t state;   /**< State of the running process ( bitmask ) */  
    uint32_t resources;  /**< What resources this task needs ( bitmask ) */  
    uint32_t esp,ebp,ebx,esi,edi;  /**< CPU State */  
    uint32_t tid; /**< Task ID */  
    uint8_t  prior;  /**< Priority */  
} task_t;

#endif