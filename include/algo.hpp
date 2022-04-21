#ifndef ALGO_HPP
#define ALGO_HPP

#include <utility>

namespace algo{
    namespace{
        void swap(int& x, int& y){
            int temp = x;
            x = y;
            y = temp;
        }

        int partition(int arr[], int start, int end, std::pair<int, int>& results)
        {
        
            int pivot = arr[start];
        
            int count{};
            for (int i = start + 1; i <= end; i++) {
                if (arr[i] <= pivot)
                    ++count, ++results.first;
            }
        
            int pivot_index = start + count;
            swap(arr[pivot_index], arr[start]);
            ++results.second;
        
            int i = start, j = end;
        
            while (i < pivot_index && j > pivot_index) {
        
                while (arr[i] <= pivot) {
                    i++;
                }
        
                while (arr[j] > pivot) {
                    j--;
                }
        
                if (i < pivot_index && j > pivot_index) {
                    swap(arr[i++], arr[j--]);
                    ++results.second;
                }

                ++results.first;
            }
        
            return pivot_index;
        }
    }

    void selection_sort(int arr[], int n, std::pair<int, int>& results);

    void bubble_sort(int arr[], int n, std::pair<int, int>& results);

    void insertion_sort(int arr[], int n, std::pair<int, int>& results);

    void quick_sort(int arr[], int begin, int end, std::pair<int, int>& results);
}

#endif