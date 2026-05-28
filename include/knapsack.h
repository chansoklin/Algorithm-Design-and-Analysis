#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "common.h"

typedef struct {
    int id;
    double weight;
    double value;
    double ratio;
} Item;

typedef struct {
    int *selected;
    double total_value;
    double total_weight;
    double exec_time;
    long long memory_used;
} KnapsackResult;

KnapsackResult brute_force(Item items[], int n, int capacity);
KnapsackResult dynamic_programming(Item items[], int n, int capacity);
KnapsackResult greedy(Item items[], int n, int capacity);
KnapsackResult backtrack_solve(Item items[], int n, int capacity);

int compare_ratio(const void *a, const void *b);

#endif