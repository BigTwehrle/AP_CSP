#ifndef ALGO_HPP
#define ALGO_HPP

namespace algo{
    template<typename func>
    void selection_sort(int arr[], int n, func compare);

    template<typename func>
    void bubble_sort(int arr[], int n, func compare);

    template<typename func>
    void insertion_sort(int arr[], int n, func compare);
}

#endif