#include "algo.hpp"
#include <iostream>

Algo::Algo(int id){ //Constructor to create an Algo based on an id
    switch (id){
        case 0: //If id is 0, Algo is called compare
            this->name = "compare";
        case 1: //If id is 1, Algo is called selection sort
            this->name = "selection sort";
            break;
        case 2: //If id is 2, Algo is called bubble sort
            this->name = "bubble sort";
            break;
        case 3: //If id is 3, Algo is called insertion sort
            this->name = "insertion sort";
            break;
        case 4: //If id is 4, Algo is called quick sort
            this->name = "quick sort";
            break;
        case 5: //If id is 5, Algo is called merge sort
            this->name = "merge sort";
            break;
        default: //Else, Algo is called invalid
            this->name = "invalid";
    }

    this->id = id;
}

const Algo& Algo::operator=(int id){ //Operator to allow assignment of Algos to integers
    return *this = Algo(id); //Creates a new Algo given an id and assigns it to the caller
}

void Algo::reset(){ //Reset's the algorithm's statistics
    this->access_count = 0;
    this->move_count = 0;
}

void Algo::selection_sort(int arr[], int n){
    //Create a start and stop time variable to time the sorting algorithms
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
    start_time = std::chrono::system_clock::now(); //Get algorithm start time
    
    for (int i = 0; i < n - 1; ++i){
        int cur = i;

        /*Each iteration, complete another iteration,
        keeping track of the current smallest (or largest)
        element and comparing it to the jth.*/
        for (int j = i + 1; j < n; ++j){
            //Update cur if more significant index is found
            if (arr[j] < arr[cur])
                cur = j;
            this->access_count += 2;
        }
        
        //Swap the ith element with cur
        swap(arr[i], arr[cur]);
        this->access_count += 2;
        ++this->move_count;
    }

    end_time = std::chrono::system_clock::now(); //Get algorithm finish time
    this->time = end_time - start_time; //Set algorithm's time to the end time - start time
}

void Algo::bubble_sort(int arr[], int n){
    //Create a start and stop time variable to time the sorting algorithms
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
    start_time = std::chrono::system_clock::now(); //Get algorithm start time

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
                this->access_count += 2;
                ++this->move_count;
            }

            this->access_count += 2;
        }
    }

    end_time = std::chrono::system_clock::now(); //Get algorithm finish time
    this->time = end_time - start_time; //Set algorithm's time to the end time - start time
}

void Algo::insertion_sort(int arr[], int n){
    //Create a start and stop time variable to time the sorting algorithms
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
    start_time = std::chrono::system_clock::now(); //Get algorithm start time

    for (int i = 1; i < n; ++i){
        int j = i;

        /*With each iteration, iterate from right to left
        until the index fits in place or reaches the end*/
        while (j > 0 && arr[j] < arr[j - 1]){
            //Swap with left adjacent index if out of place
            swap(arr[j], arr[j - 1]);
            --j;

            this->access_count += 4;
            ++this->move_count;
        }

        this->access_count += 2;
    }

    end_time = std::chrono::system_clock::now(); //Get algorithm finish time
    this->time = end_time - start_time; //Set algorithm's time to the end time - start time
}

void Algo::quick_sort(int arr[], int begin, int end){
    //Create a start and stop time variable to time the sorting algorithms
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;

    if (begin == 0 && end == LIST_SIZE - 1){
        start_time = std::chrono::system_clock::now(); //Get algorithm start time
    }

    //Sorts if the segment is greatet than one element
    if (begin < end)
    {
        //Performs recursion on several pivots to sort the list
        int pivot_index = partition(arr, begin, end);
        
        //Recursively sort each side of a pivot
        quick_sort(arr, begin, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, end);
    }

    if (begin == 0 && end == LIST_SIZE - 1){
        end_time = std::chrono::system_clock::now(); //Get algorithm finish time
        this->time = end_time - start_time; //Set algorithm's time to the end time - start time
    }
}

void Algo::merge_sort(int arr[], int begin, int end){
    //Create a start and stop time variable to time the sorting algorithms
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;

    if (begin == 0 && end == LIST_SIZE - 1){
        start_time = std::chrono::system_clock::now(); //Get algorithm start time
    }

    //Split up array until segment of maximum length 2
    if (begin < end){
        //Variable to store the middle index of the array segment
        int mid = (begin + end) / 2;
        
        //Split up the left side of the segment into smaller segments
        merge_sort(arr, begin, mid);
        //Split up the right  side of the segment into smaller segments
        merge_sort(arr, mid + 1, end);
        //Sort and merge the two segments split up
        merge(arr, begin, mid, end);    
    }

    if (begin == 0 && end == LIST_SIZE - 1){
        end_time = std::chrono::system_clock::now(); //Get algorithm finish time
        this->time = end_time - start_time; //Set algorithm's time to the end time - start time
    }
}

void Algo::swap(int& x, int& y){
    int temp = x;
    x = y;
    y = temp;
}

int Algo::partition(int arr[], int begin, int end)
{
    //Use first index in array as pivot
    int pivot_data = arr[begin];

    //Iterate list an determine pivot absolute point in sorted list
    int count{};
    for (int i = begin + 1; i <= end; i++) {
        if (arr[i] <= pivot_data)
            ++count, ++this->access_count;
    }

    //Update the posititon of the pivot in its absolute point
    int pivot_index = begin + count;
    swap(arr[pivot_index], arr[begin]);
    this->access_count += 2;
    ++this->move_count;

    int b = begin, a = end;

    /*Loops until all the smaller elements are before the pivot
    and all the larger elements are after the pivot*/
    while (b < pivot_index && a > pivot_index) {
        while (arr[b] <= pivot_data)
            ++b, ++this->access_count;

        while (arr[a] > pivot_data) 
            --a, ++this->access_count;

        /*Swaps elements on each side of pivot
        element i is before pivot and element j is after*/
        if (b < pivot_index && a > pivot_index) {
            swap(arr[b++], arr[a--]);
            this->access_count += 2;
            ++this->move_count;
        }
    }

    /*Returns the pivot index for quick_sort() to perform 
    recursion and sort both sides of the pivot*/
    return pivot_index;
}

void Algo::merge(int arr[], int const left, int const mid, int const right)
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
            ++left_index, ++this->access_count, ++this->move_count;
        }
        /*Else if the value in the right segment index
        is smaller, sub it into the merge array segment
        and increment each counter*/
        else{
            temp[merge_index - left] = arr[right_index];
            ++right_index, ++this->access_count, ++this->move_count;
        }

        this->access_count += 2;
        ++merge_index;
    }

    /*Since the end of one side of the array segment may
    be reached before the other, fill in the rest of 
    the merged array with the leftover contents 
    of the unfinished array*/
    while (left_index <= mid){ //For the left array segment
        temp[merge_index - left] = arr[left_index];
        ++left_index, ++merge_index, ++this->access_count, ++this->move_count;
    }
    while (right_index <= right){ //For the right array segment
        temp[merge_index - left] = arr[right_index];
        ++right_index, ++merge_index, ++this->access_count, ++this->move_count;
    }

    /*Once done sorting the merged array segment,
    copy each element into the actual original array*/
    for (int i = 0; i < right - left + 1; ++i)
    {
        arr[left + i] = temp[i];
        ++this->move_count;
    }
}

std::string Algo::algo_name() const{ return this->name; }
int Algo::algo_id() const{ return this->id; }
uint64_t Algo::algo_accessc() const{ return this->access_count; }
uint64_t Algo::algo_movec() const{ return this->move_count; }
std::chrono::duration<double> Algo::algo_time() const{ return this->time; }