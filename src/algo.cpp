#include "algo.hpp"

template<typename func>
void algo::selection_sort(int arr[], int n, func compare){
    int i, j, min_idx; 

    for (i = 0; i < n - 1; i++) 
    { 
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
        if (compare(arr + j, arr + min_idx)) 
            min_idx = j; 

        int temp = arr[min_idx]; 
        arr[min_idx] = arr[i]; 
        arr[i] = temp; 
    } 
}
template void algo::selection_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));

template<typename func>
void algo::bubble_sort(int arr[], int n, func compare){
    int i, j;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (compare(arr + j, arr + j + 1))
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}
template void algo::bubble_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));

template<typename func>
void algo::insertion_sort(int arr[], int n, func compare){
    int i, key, j;
    
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
template void algo::insertion_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));