#ifndef ALGO_HPP
#define ALGO_HPP

namespace algo{
    namespace{
        void swap(int& x, int& y){
            int temp = x;
            x = y;
            y = temp;
        }
    }

    template<typename func>
    int selection_sort(int arr[], int n, func compare);

    template<typename func>
    int bubble_sort(int arr[], int n, func compare);

    template<typename func>
    int insertion_sort(int arr[], int n, func compare);
}

#endif