/**
 * Kernel schedule stuff
 * @file sched.h
 */

#ifndef SCHED_H_
#define SCHED_H_

#include "common.h"
#include "task.h"

typedef struct task_list {
  task_t *task;
  struct task_list *next;
} task_list_t;

void init_scheduler (task_t *initial_task);

void task_is_ready (task_t *t);

void task_not_ready (task_t *t);

void schedule ();

#endif
