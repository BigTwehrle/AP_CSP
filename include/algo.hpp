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
    }

    template<typename func>
    std::pair<int, int> selection_sort(int arr[], int n, func compare);

    template<typename func>
    std::pair<int, int> bubble_sort(int arr[], int n, func compare);

    template<typename func>
    std::pair<int, int> insertion_sort(int arr[], int n, func compare);
}

#endif