#include "../../include/sort.h"

void test_sorting() {
    printf("\n========== Sorting Algorithm Test ==========\n");
    
    int sizes[] = {10, 100, 1000, 2000, 5000, 10000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    FILE *fp = fopen("../results/sort_results.csv", "w");
    fprintf(fp, "n,bubble_comparisons,merge_comparisons,quick_comparisons\n");
    
    for (int idx = 0; idx < num_sizes; idx++) {
        int n = sizes[idx];
        printf("\nTest size: n = %d\n", n);
        
        int *original = (int*)safe_malloc(n * sizeof(int));
        int *arr = (int*)safe_malloc(n * sizeof(int));
        
        for (int i = 0; i < n; i++) {
            original[i] = rand() % 10000;
        }
        
        if (n <= 10000) {
            copyArray(original, arr, n);
            bubble_compare = 0;
            double start = get_wall_time();
            bubbleSort(arr, n);
            double end = get_wall_time();
            printf("Bubble Sort - Comparisons: %lld, Time: %.2f ms\n", 
                   bubble_compare, (end - start) * 1000);
            fprintf(fp, "%d,%lld,", n, bubble_compare);
        } else {
            printf("Bubble Sort - Size too large, skipped\n");
            fprintf(fp, "%d,-1,", n);
        }
        
        copyArray(original, arr, n);
        merge_compare = 0;
        double start = get_wall_time();
        mergeSort(arr, 0, n - 1);
        double end = get_wall_time();
        printf("Merge Sort - Comparisons: %lld, Time: %.2f ms\n", 
               merge_compare, (end - start) * 1000);
        
        copyArray(original, arr, n);
        quick_compare = 0;
        start = get_wall_time();
        quickSort(arr, 0, n - 1);
        end = get_wall_time();
        printf("Quick Sort - Comparisons: %lld, Time: %.2f ms\n", 
               quick_compare, (end - start) * 1000);
        
        fprintf(fp, "%lld,%lld\n", merge_compare, quick_compare);
        
        free(original);
        free(arr);
    }
    
    fclose(fp);
    printf("\nSorting results saved to results/sort_results.csv\n");
}

void test_equivalence_class() {
    printf("\n========== Input Equivalence Class Test ==========\n");
    
    int n = 100;
    int *arr1 = (int*)safe_malloc(n * sizeof(int));
    int *arr2 = (int*)safe_malloc(n * sizeof(int));
    int *temp = (int*)safe_malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % 10000;
        arr2[i] = rand() % 10000;
    }
    
    printf("\nTest Array 1:\n");
    copyArray(arr1, temp, n);
    bubble_compare = 0;
    bubbleSort(temp, n);
    printf("Bubble Sort comparisons: %lld\n", bubble_compare);
    
    copyArray(arr1, temp, n);
    merge_compare = 0;
    mergeSort(temp, 0, n - 1);
    printf("Merge Sort comparisons: %lld\n", merge_compare);
    
    copyArray(arr1, temp, n);
    quick_compare = 0;
    quickSort(temp, 0, n - 1);
    printf("Quick Sort comparisons: %lld\n", quick_compare);
    
    printf("\nTest Array 2:\n");
    copyArray(arr2, temp, n);
    bubble_compare = 0;
    bubbleSort(temp, n);
    printf("Bubble Sort comparisons: %lld\n", bubble_compare);
    
    copyArray(arr2, temp, n);
    merge_compare = 0;
    mergeSort(temp, 0, n - 1);
    printf("Merge Sort comparisons: %lld\n", merge_compare);
    
    copyArray(arr2, temp, n);
    quick_compare = 0;
    quickSort(temp, 0, n - 1);
    printf("Quick Sort comparisons: %lld\n", quick_compare);
    
    free(arr1);
    free(arr2);
    free(temp);
}