/**
 * Defines the interface for monitor stuff.
 * This is from JamesM's Kernel
 * @file monitor.h
 */

#ifndef MONITOR_H
#define MONITOR_H

#include <posk/common.h>

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

void printk (const char *fmt, ...);


#endif // MONITOR_H
