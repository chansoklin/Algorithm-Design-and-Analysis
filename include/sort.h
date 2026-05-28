#ifndef SORT_H
#define SORT_H

#include "common.h"

extern long long bubble_compare;
extern long long merge_compare;
extern long long quick_compare;

void bubbleSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);
void copyArray(int src[], int dest[], int n);
void printArray(int arr[], int n);
void merge(int arr[], int left, int mid, int right);
int partition(int arr[], int low, int high);

#endif