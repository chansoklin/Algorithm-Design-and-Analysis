#include "../../include/knapsack.h"

KnapsackResult brute_force(Item items[], int n, int capacity) {
    KnapsackResult result;
    result.selected = (int*)calloc(n, sizeof(int));
    result.total_value = 0;
    result.total_weight = 0;
    
    double start_time = get_wall_time();
    
    int total_subsets = 1 << n;
    long long memory_used = sizeof(int) * n + sizeof(double) * 2;
    
    for (int mask = 0; mask < total_subsets; mask++) {
        double current_weight = 0;
        double current_value = 0;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                current_weight += items[i].weight;
                current_value += items[i].value;
            }
        }
        
        if (current_weight <= capacity && current_value > result.total_value) {
            result.total_value = current_value;
            result.total_weight = current_weight;
            
            for (int i = 0; i < n; i++) {
                result.selected[i] = (mask & (1 << i)) ? 1 : 0;
            }
        }
    }
    
    result.exec_time = (get_wall_time() - start_time) * 1000;
    result.memory_used = memory_used;
    
    return result;
}