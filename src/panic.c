/**
 * OMGWTFBBQ
 * @file panic.c
 */

#include <posk/panic.h>
#include <posk/common.h>

/** 
 * PANIC
 * @param message to panic to the user
 */
void panic (const char *msg) {
  //asm volatile("cli"); <-- this fucking broke everything
  printk("*** SYSTEM PANIC ***\n");
  printk("%s\n", msg);
  printk("********************\n");
  for( ;; );
}
