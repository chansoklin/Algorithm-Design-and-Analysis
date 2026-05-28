#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

// Function declarations
double get_wall_time();
void swap(int *a, int *b);
void init_rand();
void* safe_malloc(size_t size);

#endif