#include "algo.hpp"
#include <iostream>
#include <chrono>

template<typename func>
std::pair<int, int> algo::selection_sort(int arr[], int n, func compare){
    int iter_num{}, swap_num{};

    for (int i = 0; i < n - 1; ++i){
        int cur = i;

        /*Each iteration, complete another iteration,
        keeping track of the current smallest (or largest)
        element and comparing it to the jth.*/
        for (int j = i + 1; j < n; ++j){
            //Update cur if more significant index is found
            if (compare(&arr[j], &arr[cur]))
                cur = j;
            ++iter_num;
            //Swap the ith element with cur
        }
        
        swap(arr[i], arr[cur]);
        ++swap_num;
    }

    return {iter_num, swap_num};
}
template std::pair<int, int> algo::selection_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));

template<typename func>
std::pair<int, int> algo::bubble_sort(int arr[], int n, func compare){
    int iter_num{}, swap_num{};

    for (int i = 0; i < n - 1; ++i){
        /*With each iteration, perform another internal
        iteration, decreasing the magnitude each time
        i increments for efficiency.*/
        for (int j = 0; j < n - i - 1; ++j){
            /*Swap two adjacent indecies if the greater
            index is more significant*/
            if (compare(&arr[j + 1], &arr[j])){
                swap(arr[j], arr[j + 1]);
                ++swap_num;
            }

            ++iter_num;
        }
    }

    return {iter_num, swap_num};
}
template std::pair<int, int> algo::bubble_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));

template<typename func>
std::pair<int, int> algo::insertion_sort(int arr[], int n, func compare){
    int iter_num{}, swap_num{};

    for (int i = 1; i < n; ++i){
        int j = i;

        /*With each iteration, iterate from right to left
        until the index fits in place or reaches the end*/
        while (j > 0 && compare(&arr[j], &arr[j - 1])){
            //Swap with left adjacent index if out of place
            swap(arr[j], arr[j - 1]);
            --j;

            ++iter_num, ++swap_num;
        }
    }

    return {iter_num, swap_num};
}
template std::pair<int, int> algo::insertion_sort<bool (*)(int*, int*)>(int[], int n, bool (*)(int*, int*));