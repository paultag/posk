/**
 * Kernel schedule stuff
 * @file sched.h
 */

#ifndef SCHED_H_
#define SCHED_H_

#include "common.h"
#include "task.h"

/**
 * The task linked list object.
 */
typedef struct task_list {
  task_t *task;             /**< Composed Bie-otch process. */
  struct task_list *next;   /**< The next goddamn task. Google "Linked List" */
} task_list_t;

void init_scheduler (task_t *initial_task);

void task_is_ready (task_t *t);

void task_not_ready (task_t *t);

void schedule ();

#endif
