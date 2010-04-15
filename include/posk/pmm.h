/**
 * Physical Memory management stuff
 * @file pmm.h
 */

#ifndef PMM_H_
#define PMM_H_ truedat

#include "common.h"

#define PMM_STACK_ADDR 0xFF000000

void init_pmm (uint32_t start);

uint32_t pmm_alloc_page ();

void pmm_free_page (uint32_t p);

#endif
