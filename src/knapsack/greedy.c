#include "../../include/knapsack.h"

int compare_ratio(const void *a, const void *b) {
    Item *item1 = (Item*)a;
    Item *item2 = (Item*)b;
    double ratio1 = item1->value / item1->weight;
    double ratio2 = item2->value / item2->weight;
    if (ratio2 > ratio1) return 1;
    if (ratio2 < ratio1) return -1;
    return 0;
}

KnapsackResult greedy(Item items[], int n, int capacity) {
    KnapsackResult result;
    result.selected = (int*)calloc(n, sizeof(int));
    result.total_value = 0;
    result.total_weight = 0;
    
    double start_time = get_wall_time();
    
    Item *sorted_items = (Item*)safe_malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++) {
        sorted_items[i] = items[i];
        sorted_items[i].id = i;
    }
    
    qsort(sorted_items, n, sizeof(Item), compare_ratio);
    
    int current_weight = 0;
    for (int i = 0; i < n; i++) {
        if (current_weight + sorted_items[i].weight <= capacity) {
            current_weight += sorted_items[i].weight;
            result.total_weight += sorted_items[i].weight;
            result.total_value += sorted_items[i].value;
            result.selected[sorted_items[i].id] = 1;
        }
    }
    
    long long memory_used = n * sizeof(Item) + n * sizeof(int);
    
    free(sorted_items);
    
    result.exec_time = (get_wall_time() - start_time) * 1000;
    result.memory_used = memory_used;
    
    return result;
}