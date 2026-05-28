#include "../../include/knapsack.h"

KnapsackResult dynamic_programming(Item items[], int n, int capacity) {
    KnapsackResult result;
    result.selected = (int*)calloc(n, sizeof(int));
    result.total_value = 0;
    result.total_weight = 0;
    
    double start_time = get_wall_time();
    
    double **dp = (double**)safe_malloc((n + 1) * sizeof(double*));
    int **keep = (int**)safe_malloc((n + 1) * sizeof(int*));
    
    for (int i = 0; i <= n; i++) {
        dp[i] = (double*)calloc(capacity + 1, sizeof(double));
        keep[i] = (int*)calloc(capacity + 1, sizeof(int));
    }
    
    long long memory_used = (n + 1) * (capacity + 1) * (sizeof(double) + sizeof(int));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (items[i-1].weight <= w) {
                double include = dp[i-1][w - (int)items[i-1].weight] + items[i-1].value;
                double exclude = dp[i-1][w];
                
                if (include > exclude) {
                    dp[i][w] = include;
                    keep[i][w] = 1;
                } else {
                    dp[i][w] = exclude;
                    keep[i][w] = 0;
                }
            } else {
                dp[i][w] = dp[i-1][w];
                keep[i][w] = 0;
            }
        }
    }
    
    result.total_value = dp[n][capacity];
    
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (keep[i][w]) {
            result.selected[i-1] = 1;
            result.total_weight += items[i-1].weight;
            w -= (int)items[i-1].weight;
        }
    }
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
        free(keep[i]);
    }
    free(dp);
    free(keep);
    
    result.exec_time = (get_wall_time() - start_time) * 1000;
    result.memory_used = memory_used;
    
    return result;
}