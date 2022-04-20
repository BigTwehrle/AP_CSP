#include "algo.hpp"
#include <iostream>
#include <chrono>

template<typename func>
int algo::selection_sort(int arr[], int n, func compare){
    int iter_num{};

    //Iterate over the list n - 1 times
    for (int i = 0; i < n - 1; ++i){
        int cur = i;
        /*Each iteration, complete another iteration,
        keeping track of the current smallest (or largest)
        element and comparing it to the jth.*/
        for (int j = i + 1; j < n; ++j)
            //Update cur if more significant index is found
            if (compare(&arr[j], &arr[cur]))
            {
                cur = j;
                ++iter_num;
            }
        //Swap the ith element with cur
        int temp = arr[i];
        arr[i] = arr[cur];
        arr[cur] = temp;
    }

    return iter_num;
}
template int algo::selection_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));

template<typename func>
int algo::bubble_sort(int arr[], int n, func compare){
    int iter_num{};

    //Iterate over the list n - 1 times
    for (int i = 0; i < n - 1; ++i){
        /*With each iteration, perform another internal
        iteration, decreasing the magnitude each time
        i increments for efficiency.*/
        for (int j = 0; j < n - i - 1; ++j){
            /*Swap two adjacent indecies if the greater
            index is more significant*/
            if (compare(&arr[j + 1], &arr[j])){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                ++iter_num;
            }
        }
    }

    return iter_num;
}
template int algo::bubble_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));

template<typename func>
int algo::insertion_sort(int arr[], int n, func compare){
    int iter_num{};
    
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
template int algo::insertion_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));