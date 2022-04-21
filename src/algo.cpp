#include "algo.hpp"
#include <iostream>
#include <chrono>

void algo::selection_sort(int arr[], int n, std::pair<int, int>& results){
    for (int i = 0; i < n - 1; ++i){
        int cur = i;

        /*Each iteration, complete another iteration,
        keeping track of the current smallest (or largest)
        element and comparing it to the jth.*/
        for (int j = i + 1; j < n; ++j){
            //Update cur if more significant index is found
            if (arr[j] < arr[cur])
                cur = j;
            ++results.first;
        }
        
        //Swap the ith element with cur
        swap(arr[i], arr[cur]);
        ++results.second;
    }
}

void algo::bubble_sort(int arr[], int n, std::pair<int, int>& results){
    int iter_num{}, swap_num{};

    for (int i = 0; i < n - 1; ++i){
        /*With each iteration, perform another internal
        iteration, decreasing the magnitude each time
        i increments for efficiency.*/
        for (int j = 0; j < n - i - 1; ++j){
            /*Swap two adjacent indecies if the greater
            index is more significant*/
            if (arr[j + 1] < arr[j]){
                swap(arr[j], arr[j + 1]);
                ++results.second;
            }

            ++results.first;
        }
    }
}

void algo::insertion_sort(int arr[], int n, std::pair<int, int>& results){
    for (int i = 1; i < n; ++i){
        int j = i;

        /*With each iteration, iterate from right to left
        until the index fits in place or reaches the end*/
        while (j > 0 && arr[j] < arr[j - 1]){
            //Swap with left adjacent index if out of place
            swap(arr[j], arr[j - 1]);
            --j;

            ++results.first, ++results.second;
        }
    }
}

void algo::quick_sort(int arr[], int begin, int end, std::pair<int, int>& results){
    //Sorts if the segment is greatet than one element
    if (begin < end)
    {
        //Performs recursion on several pivots to sort the list
        int pivot_index = partition(arr, begin, end, results);
        
        //Recursively sort each side of a pivot
        quick_sort(arr, begin, pivot_index - 1, results);
        quick_sort(arr, pivot_index + 1, end, results);
    }
}

void algo::merge_sort(int arr[], int begin, int end, std::pair<int, int>& results){
    //Split up array until segment of maximum length 2
    if (begin < end){
        //Variable to store the middle index of the array segment
        int mid = (begin + end) / 2;
        
        //Split up the left side of the segment into smaller segments
        merge_sort(arr, begin, mid, results);
        //Split up the right  side of the segment into smaller segments
        merge_sort(arr, mid + 1, end, results);
        //Sort and merge the two segments split up
        merge(arr, begin, mid, end, results);    
    }
}