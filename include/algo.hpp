#ifndef ALGO_HPP
#define ALGO_HPP

#include <cstdint>
#include <chrono>
#include <string>

/*Structure called Algo which contains information
about the performance of the sorting method as well as
general metadata used by other functionality*/
class Algo{
    public:
        Algo() = default;
        explicit Algo(int id); //Constructor to create an Algo based on an id
    
        const Algo& operator=(int id); //Operator to allow assignment of Algos to integers

        //Declare sorting algorithms
        void selection_sort(int arr[], int n);
        void bubble_sort(int arr[], int n);
        void insertion_sort(int arr[], int n);
        void quick_sort(int arr[], int begin, int end);
        void merge_sort(int arr[], int begin, int end);

        //Get functions, do not allow for modifications due to const specifier
        std::string algo_name() const;
        int algo_id() const;
        uint64_t algo_accessc() const;
        uint64_t algo_movec() const;
        std::chrono::duration<double> algo_time() const;

        //Number of algorithms available to choose from
        static constexpr int num_options{5};

    private:
        std::string name; //Indicates the name of the sorting method
        int id; //Associates an id with the sorting method
        //Counters for the number of array accesses and data moves performed by the sorting method
        uint64_t access_count{}, move_count{}; 
        std::chrono::duration<double> time{}; //Variable to store the time taken to sort the list using a method

        //Swap the data in two elements passed to swap()
        void swap(int& x, int& y);

        //Create pivots in an array of data to sort the array
        int partition(int arr[], int begin, int end);

        //Sort and merge two subarrays into one larger sorted array
        void merge(int arr[], int const left, int const mid, int const right);
};

#endif