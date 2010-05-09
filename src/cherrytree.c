#include <posk/cherrytree.h>
#include <posk/task.h>
#include <posk/slab.h>
#include <posk/sched.h>

ct_task_t * task_ll_head = 0;
ct_task_t * valid_task_ll_head = 0;
static uint32_t counter = 0;

void newTask(uint32_t pnumber, int32_t total_timeunits, uint16_t resources, uint16_t priority, uint32_t start_time) {  
  ct_task_t * task = (ct_task_t *) kmalloc (sizeof (ct_task_t));
  
  task->pnumber = pnumber;
  task->total_timeunits = total_timeunits;
  task->remaining_timeunits = total_timeunits;
  task->resources = resources;
  task->priority = priority;
  task->start_time = start_time;
  task->end_time = -1;
  task->next = 0;
  
  if(task_ll_head == 0) {
      task_ll_head = task;
  } else {
      ct_task_t * iter = task_ll_head;
      while(iter->next != 0) {
	  iter = (ct_task_t *) iter->next;
      }
      iter->next = (void *) task;
  }

}

void runTaskFor(uint32_t pnumber, int32_t timeunits) {
  if(pnumber == 0) {
    counter++;
    return;
    }  
  ct_task_t * iter = task_ll_head;
    while(iter->pnumber != pnumber) {
      iter = ( ct_task_t * ) iter->next;
    }
    if(iter->remaining_timeunits < timeunits && iter->remaining_timeunits > 0) {
	doNothing(iter->remaining_timeunits, pnumber);
	iter->remaining_timeunits = 0;
    } else {
	doNothing(timeunits, pnumber);
	iter->remaining_timeunits -= timeunits;
    }
}

void runTaskTillEnd(uint32_t pnumber) {
    if(pnumber == 0) {
    counter++;
    return;
    }
    ct_task_t * iter = task_ll_head;
    while(iter->pnumber != pnumber) {
      iter = ( ct_task_t * ) iter->next;
    }
    if(iter->remaining_timeunits > 0) {
      doNothing(iter->remaining_timeunits, pnumber);
      iter->remaining_timeunits = 0;
    }
}

void doNothing(uint32_t timeunits, uint32_t pnumber) {
    while(timeunits > 0) {
	printk("executing pnumber %d\n", pnumber);
	counter++;
	timeunits--;
    }
    return;
}

void set_valid_tasks() {
    valid_task_ll_head = 0;
    ct_task_t * iter = task_ll_head;
    
    while(iter) {
	if(iter->remaining_timeunits > 0 && iter->start_time <= counter) {
	    ct_task_t * task = (ct_task_t *) kmalloc (sizeof (ct_task_t));
  
	    task->pnumber = iter->pnumber;
	    task->total_timeunits = iter->total_timeunits;
	    task->remaining_timeunits = iter->remaining_timeunits;
	    task->resources = iter->resources;
	    task->priority = iter->priority;
	    task->start_time = iter->start_time;
	    task->end_time = -1;
	    task->next = 0;
	    
	    if(valid_task_ll_head == 0) {
		valid_task_ll_head = task;
	    } else {
		ct_task_t * v_iter = valid_task_ll_head;
		while(v_iter->next) v_iter = (ct_task_t *) v_iter->next;
		v_iter->next = (void *)task;
	    }
	}
      
	iter = (ct_task_t *)iter->next;
    }
}

void ct_scheduler() {
  set_valid_tasks();
  
    uint32_t shortest_seen = 0;
    uint32_t pnumber_to_run = 0;
    
    ct_task_t * iter = valid_task_ll_head;

    while(iter) {
	if(shortest_seen == 0 || shortest_seen > iter->remaining_timeunits) {
	    shortest_seen = iter->remaining_timeunits;
	    pnumber_to_run = iter->pnumber;
	}
	iter = (ct_task_t *)iter->next;
    }
    
    runTaskFor(pnumber_to_run, 4);
}
