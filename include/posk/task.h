#ifndef TASK_H_
#define TASK_H_ YUP

#include "common.h"

/**
 * Holds task data about things, and stuff.
 */
typedef struct {
    uint32_t state;      /**< State of the running process ( bitmask ) */  
    uint32_t resources;  /**< What resources this task needs ( bitmask ) */  
    uint32_t esp;        /**< CPU State, Stack Pointer */  
    uint32_t ebp;        /**< CPU State, Base Pointer */  
    uint32_t ebx;        /**< CPU State, G.P. Register */  
    uint32_t esi;        /**< CPU State, G.P. Register */  
    uint32_t edi;        /**< CPU State, G.P. Register */  
    uint32_t tid;        /**< Task ID */  
    uint8_t  prior;      /**< Priority */
} task_t;

task_t * create_dumb_task(int32_t time, uint32_t pnumber, uint32_t * stack);


#endif