#include <posk/cherrytree.h>
#include <posk/task.h>
#include <posk/slab.h>
#include <posk/sched.h>

ct_task_t * task_ll_head = 0;
static void newKTask(uint32_t time, uint32_t pnumber);

void newTask(uint32_t pnumber, int32_t total_timeunits, uint16_t resources, uint16_t priority) {  
  printk("newTask: making pnumber %d\n", pnumber);
  ct_task_t * task = (ct_task_t *) kmalloc (sizeof (ct_task_t));
  
  task->pnumber = pnumber;
  task->total_timeunits = total_timeunits;
  task->remaining_timeunits = total_timeunits;
  task->resources = resources;
  task->priority = priority;
  task->next = 0;
  
  if(task_ll_head == 0) {
      task_ll_head = task;
  } else {
      ct_task_t * iter = task_ll_head;
      while(iter->next != 0) {
	  iter = iter->next;
      }
      iter->next = task;
  }
  
  printk("newTask: done making pnumber %d\n", pnumber);
  
  
}

void runTaskFor(uint32_t pnumber, int32_t timeunits) {
    ct_task_t * iter = task_ll_head;
    while(iter->pnumber != pnumber) {
      iter = ( ct_task_t * ) iter->next;
    }
    if(iter->remaining_timeunits < timeunits && iter->remaining_timeunits > 0) {
	newKTask(iter->remaining_timeunits, pnumber);
	iter->remaining_timeunits = 0;
    } else {
	newKTask(timeunits, pnumber);
	iter->remaining_timeunits -= timeunits;
    }
}

void runTaskTillEnd(uint32_t pnumber) {
    ct_task_t * iter = task_ll_head;
    while(iter->pnumber != pnumber) {
      iter = ( ct_task_t * ) iter->next;
    }
    if(iter->remaining_timeunits > 0) {
      newKTask(iter->remaining_timeunits, pnumber);
      iter->remaining_timeunits = 0;
    }
}

void sleep(uint32_t timeunits) {
  uint32_t * stack = (uint32_t*) kmalloc (0x100) + 0xF0;
  task_t * t = (task_t *)ksleep(timeunits, stack);
  task_is_ready(t);
}

void newKTask(uint32_t time, uint32_t pnumber) {
    printk("KTASK: Creating new process %d for length %d\n", pnumber, time );
    uint32_t * stack = (uint32_t*) kmalloc (0x100) + 0xF0;
    task_t * t = (task_t *)create_dumb_task(time, pnumber, stack);
    task_is_ready(t);
}
