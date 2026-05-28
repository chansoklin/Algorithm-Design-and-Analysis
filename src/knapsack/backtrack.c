#include "../../include/knapsack.h"

static Item *bt_items;
static int bt_n;
static int bt_capacity;
static int *bt_best_selection;
static double bt_best_value;
static double bt_curr_value;
static double bt_curr_weight;

static double bound(int level) {
    double remaining = bt_capacity - bt_curr_weight;
    double bound_val = bt_curr_value;
    int i = level;
    
    while (i < bt_n && bt_items[i].weight <= remaining) {
        remaining -= bt_items[i].weight;
        bound_val += bt_items[i].value;
        i++;
    }
    
    if (i < bt_n && remaining > 0) {
        bound_val += (bt_items[i].value / bt_items[i].weight) * remaining;
    }
    
    return bound_val;
}

static void dfs(int level) {
    if (level == bt_n) {
        if (bt_curr_value > bt_best_value) {
            bt_best_value = bt_curr_value;
            for (int i = 0; i < bt_n; i++) {
                bt_best_selection[i] = 0;
            }
        }
        return;
    }
    
    if (bound(level) <= bt_best_value) {
        return;
    }
    
    if (bt_curr_weight + bt_items[level].weight <= bt_capacity) {
        bt_curr_weight += bt_items[level].weight;
        bt_curr_value += bt_items[level].value;
        dfs(level + 1);
        bt_curr_weight -= bt_items[level].weight;
        bt_curr_value -= bt_items[level].value;
    }
    
    dfs(level + 1);
}

KnapsackResult backtrack_solve(Item items[], int n, int capacity) {
    KnapsackResult result;
    result.selected = (int*)calloc(n, sizeof(int));
    result.total_value = 0;
    result.total_weight = 0;
    
    double start_time = get_wall_time();
    
    if (n > 30) {
        result.exec_time = 0;
        result.memory_used = 0;
        return result;
    }
    
    bt_items = (Item*)safe_malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++) {
        bt_items[i] = items[i];
        bt_items[i].ratio = items[i].value / items[i].weight;
    }
    
    qsort(bt_items, n, sizeof(Item), compare_ratio);
    
    bt_n = n;
    bt_capacity = capacity;
    bt_best_selection = (int*)calloc(n, sizeof(int));
    bt_best_value = 0;
    bt_curr_value = 0;
    bt_curr_weight = 0;
    
    dfs(0);
    
    result.total_value = bt_best_value;
    
    double temp_w = 0;
    for (int i = 0; i < n && temp_w < bt_best_value; i++) {
        if (temp_w + bt_items[i].weight <= capacity) {
            temp_w += bt_items[i].weight;
            result.selected[bt_items[i].id] = 1;
            result.total_weight += bt_items[i].weight;
        }
    }
    
    free(bt_items);
    free(bt_best_selection);
    
    result.exec_time = (get_wall_time() - start_time) * 1000;
    result.memory_used = n * (sizeof(Item) + sizeof(int));
    
    return result;
}