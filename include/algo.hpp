#ifndef ALGO_HPP
#define ALGO_HPP

#include <utility>
#include <cstdint>

namespace algo{
    namespace{
        //Swap the data in two elements passed to swap()
        void swap(int& x, int& y){
            int temp = x;
            x = y;
            y = temp;
        }

        int partition(int arr[], int begin, int end, std::pair<uint64_t, uint64_t>& results)
        {
            //Use first index in array as pivot
            int pivot_data = arr[begin];

            //Iterate list an determine pivot absolute point in sorted list
            int count{};
            for (int i = begin + 1; i <= end; i++) {
                if (arr[i] <= pivot_data)
                    ++count, ++results.first;
            }

            //Update the posititon of the pivot in its absolute point
            int pivot_index = begin + count;
            swap(arr[pivot_index], arr[begin]);
            results.first += 2;
            ++results.second;
        
            int b = begin, a = end;

            /*Loops until all the smaller elements are before the pivot
            and all the larger elements are after the pivot*/
            while (b < pivot_index && a > pivot_index) {
                while (arr[b] <= pivot_data)
                    ++b, ++results.first;
        
                while (arr[a] > pivot_data) 
                    --a, ++results.first;

                /*Swaps elements on each side of pivot
                element i is before pivot and element j is after*/
                if (b < pivot_index && a > pivot_index) {
                    swap(arr[b++], arr[a--]);
                    results.first += 2;
                    ++results.second;
                }
            }

            /*Returns the pivot index for quick_sort() to perform 
            recursion and sort both sides of the pivot*/
            return pivot_index;
        }

        void merge(int arr[], int const left, int const mid, int const right, std::pair<uint64_t, uint64_t>& results)
        {
            int left_index = left, //First index of the left array segment
                right_index = mid + 1, //First index of the right array segment
                merge_index = left; //First index of the merged array segment
            int* temp = new int[right - left + 1]; //Created the container for the merged array segment
            
            /*Loop until either the end of the left segment
            or right segment has been reached*/
            while (left_index <= mid && right_index <= right){
                /*If the value in the left segment index
                is smaller, sub it into the merge array segment 
                and increment each counter*/
                if (arr[left_index] < arr[right_index]){
                    temp[merge_index - left] = arr[left_index];
                    ++left_index, ++results.first, ++results.second;
                }
                /*Else if the value in the right segment index
                is smaller, sub it into the merge array segment
                and increment each counter*/
                else{
                    temp[merge_index - left] = arr[right_index];
                    ++right_index, ++results.first, ++results.second;
                }

                results.first += 2;
                ++merge_index;
            }

            /*Since the end of one side of the array segment may
            be reached before the other, fill in the rest of 
            the merged array with the leftover contents 
            of the unfinished array*/
            while (left_index <= mid){ //For the left array segment
                temp[merge_index - left] = arr[left_index];
                ++left_index, ++merge_index, ++results.first, ++results.second;
            }
            while (right_index <= right){ //For the right array segment
                temp[merge_index - left] = arr[right_index];
                ++right_index, ++merge_index, ++results.first, ++results.second;
            }

            /*Once done sorting the merged array segment,
            copy each element into the actual original array*/
            for (int i = 0; i < right - left + 1; ++i)
            {
                arr[left + i] = temp[i];
                ++results.second;
            }
        }
    }

    void selection_sort(int arr[], int n, std::pair<uint64_t, uint64_t>& results);

    void bubble_sort(int arr[], int n, std::pair<uint64_t, uint64_t>& results);

    void insertion_sort(int arr[], int n, std::pair<uint64_t, uint64_t>& results);

    void quick_sort(int arr[], int begin, int end, std::pair<uint64_t, uint64_t>& results);

    void merge_sort(int arr[], int begin, int end, std::pair<uint64_t, uint64_t>& results);
}

#endif