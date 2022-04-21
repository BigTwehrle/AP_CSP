#ifndef ALGO_HPP
#define ALGO_HPP

#include <utility>

namespace algo{
    namespace{
        //Swap the data in two elements passed to swap()
        void swap(int& x, int& y){
            int temp = x;
            x = y;
            y = temp;
        }

        int partition(int arr[], int begin, int end, std::pair<int, int>& results)
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
            ++results.second;
        
            int b = begin, a = end;

            /*Loops until all the smaller elements are before the pivot
            and all the larger elements are after the pivot*/
            while (b < pivot_index && a > pivot_index) {
                while (arr[b] <= pivot_data)
                    ++b;
        
                while (arr[a] > pivot_data) 
                    --a;

                /*Swaps elements on each side of pivot
                element i is before pivot and element j is after*/
                if (b < pivot_index && a > pivot_index) {
                    swap(arr[b++], arr[a--]);
                    ++results.second;
                }

                ++results.first;
            }

            /*Returns the pivot index for quick_sort() to perform 
            recursion and sort both sides of the pivot*/
            return pivot_index;
        }

        void merge(){
            
        }
    }

    void selection_sort(int arr[], int n, std::pair<int, int>& results);

    void bubble_sort(int arr[], int n, std::pair<int, int>& results);

    void insertion_sort(int arr[], int n, std::pair<int, int>& results);

    void quick_sort(int arr[], int begin, int end, std::pair<int, int>& results);

    void merge_sort(int arr[], int begin, int end, std::pair<int, int>& results);
}

#endif