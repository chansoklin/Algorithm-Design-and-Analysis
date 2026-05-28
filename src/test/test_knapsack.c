#include "../../include/knapsack.h"

void test_small_scale() {
    printf("\n========== Small Scale Exact Comparison ==========\n");
    
    int n = 5;
    int capacity = 10;
    Item items[] = {
        {1, 2, 6, 0},
        {2, 2, 3, 0},
        {3, 6, 5, 0},
        {4, 5, 4, 0},
        {5, 4, 6, 0}
    };
    
    printf("\nTest: 5 items, capacity=10\n");
    printf("Weights: [2,2,6,5,4], Values: [6,3,5,4,6]\n");
    printf("Expected optimal: items 1,2,5, total value=15\n\n");
    
    KnapsackResult brute_result = brute_force(items, n, capacity);
    printf("Brute Force: Value=%.2f, Weight=%.2f, Time=%.2f ms\n", 
           brute_result.total_value, brute_result.total_weight, brute_result.exec_time);
    
    KnapsackResult dp_result = dynamic_programming(items, n, capacity);
    printf("DP: Value=%.2f, Weight=%.2f, Time=%.2f ms\n", 
           dp_result.total_value, dp_result.total_weight, dp_result.exec_time);
    
    KnapsackResult greedy_result = greedy(items, n, capacity);
    printf("Greedy: Value=%.2f, Weight=%.2f, Time=%.2f ms\n", 
           greedy_result.total_value, greedy_result.total_weight, greedy_result.exec_time);
    
    KnapsackResult backtrack_result = backtrack_solve(items, n, capacity);
    printf("Backtracking: Value=%.2f, Weight=%.2f, Time=%.2f ms\n", 
           backtrack_result.total_value, backtrack_result.total_weight, backtrack_result.exec_time);
    
    free(brute_result.selected);
    free(dp_result.selected);
    free(greedy_result.selected);
    free(backtrack_result.selected);
}

void test_knapsack() {
    printf("\n========== 0-1 Knapsack Test ==========\n");
    
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};
    int capacities[] = {100, 500, 1000};
    
    FILE *fp = fopen("../results/knapsack_results.csv", "w");
    fprintf(fp, "n,capacity,algorithm,total_value,total_weight,time_ms,memory_bytes\n");
    
    for (int cap_idx = 0; cap_idx < 3; cap_idx++) {
        int capacity = capacities[cap_idx];
        printf("\n\n========== Capacity: %d ==========\n", capacity);
        
        for (int size_idx = 0; size_idx < 7; size_idx++) {
            int n = sizes[size_idx];
            printf("\nTesting n=%d, capacity=%d\n", n, capacity);
            
            Item *items = (Item*)safe_malloc(n * sizeof(Item));
            for (int i = 0; i < n; i++) {
                items[i].id = i + 1;
                items[i].weight = (rand() % 100) + 1;
                items[i].value = (rand() % 901) + 100;
                items[i].value = round(items[i].value * 100) / 100;
            }
            
            KnapsackResult greedy_result = greedy(items, n, capacity);
            fprintf(fp, "%d,%d,greedy,%.2f,%.2f,%.2f,%lld\n", 
                    n, capacity, greedy_result.total_value, 
                    greedy_result.total_weight, greedy_result.exec_time, 
                    greedy_result.memory_used);
            
            if (n <= 500 && capacity <= 1000) {
                KnapsackResult dp_result = dynamic_programming(items, n, capacity);
                fprintf(fp, "%d,%d,dp,%.2f,%.2f,%.2f,%lld\n", 
                        n, capacity, dp_result.total_value, 
                        dp_result.total_weight, dp_result.exec_time, 
                        dp_result.memory_used);
                free(dp_result.selected);
            }
            
            free(greedy_result.selected);
            free(items);
        }
    }
    
    fclose(fp);
    printf("\nKnapsack results saved to results/knapsack_results.csv\n");
}