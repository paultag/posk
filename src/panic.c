/**
 * OMGWTFBBQ
 * @file panic.c
 */

#include <posk/panic.h>
#include <posk/common.h>

extern tick;

/** 
 * PANIC
 * @param message to panic to the user
 */
void panic (const char *msg) {
  asm volatile("cli"); //<-- this fucking broke everything
  printk ( "Panic!!\n" );
  printk ( "AAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHHH\n" );
  for( ;; );
}
