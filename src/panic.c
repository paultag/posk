#include <posk/panic.h>
#include <posk/common.h>

void panic (const char *msg) {
  printk("*** SYSTEM PANIC ***\n");
  printk("%s\n", msg);
  printk("********************\n");
  for( ;; );
}