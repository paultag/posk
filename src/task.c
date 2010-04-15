#include <posk/task.h>

task_t * current_task;
uint32_t next_tid = 0;

static void task_exit();

task_t * init_threading() {
  task_t * task = (task_t*)kmalloc( sizeof(task_t) );
  task->tid = next_tid++;
  
  current_task = task;
  
  return task;
}

int dummy_func(uint32_t iter, uint32_t tid) {
  printk("in dummy_func\n");
  while(iter > 0) {
	printk("exec tid %d\n", tid);
	iter--;
    }
    return 0;
}


task_t * create_dumb_task(uint32_t time, uint32_t * stack) {
   task_t * task = (task_t*)kmalloc( sizeof(task_t) );
   memset(task, 0, sizeof(task_t));
   task->tid = next_tid++;
   
   *--stack = task->tid;
   *--stack = time;
   *--stack = (uint32_t)&task_exit;
   *--stack = (uint32_t)&dummy_func;
   *--stack = 0;
   task->ebp = (uint32_t)stack;
   task->esp = (uint32_t)stack;
   
   return task;
}

void switch_task(task_t * next) {
  
  asm volatile ("mov %%esp, %0" : "=r" (current_task->esp));
  asm volatile ("mov %%ebp, %0" : "=r" (current_task->ebp));
  asm volatile ("mov %%ebx, %0" : "=r" (current_task->ebx));
  asm volatile ("mov %%esi, %0" : "=r" (current_task->esi));
  asm volatile ("mov %%edi, %0" : "=r" (current_task->edi));

  current_task = next;

  asm volatile ("mov %0, %%edi" : : "r" (next->edi));
  asm volatile ("mov %0, %%esi" : : "r" (next->esi));
  asm volatile ("mov %0, %%ebx" : : "r" (next->ebx));
  asm volatile ("mov %0, %%esp" : : "r" (next->esp));
  asm volatile ("mov %0, %%ebp" : : "r" (next->ebp));
}

void task_exit () {
    register uint32_t val asm ("eax");
    
    printk("thread exited with value %d\n", val);
    for(;;);
}