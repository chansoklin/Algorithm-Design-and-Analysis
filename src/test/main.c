#include "../../include/common.h"
#include "../../include/sort.h"
#include "../../include/knapsack.h"

void test_sorting();
void test_equivalence_class();
void test_knapsack();
void test_small_scale();

int main() {
    printf("========================================\n");
    printf("    Algorithm Design and Analysis\n");
    printf("    Yunnan University - Class of 2024\n");
    printf("========================================\n");
    
    init_rand();
    system("mkdir -p ../results");
    
    printf("\nPart 1: Sorting Algorithm Test\n");
    printf("----------------------------------------\n");
    test_equivalence_class();
    test_sorting();
    
    printf("\nPart 2: 0-1 Knapsack Problem Test\n");
    printf("----------------------------------------\n");
    test_small_scale();
    test_knapsack();
    
    printf("\n========================================\n");
    printf("All tests completed!\n");
    printf("Results saved to results/ directory\n");
    printf("========================================\n");
    
    return 0;
}