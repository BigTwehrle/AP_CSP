#include <iostream>
#include <time.h>
#include <vector>
#include <limits>
#include <thread>
#include <chrono>
#include "algo.hpp"

#define LIST_SIZE 50000 //Macro defining the size of the list to be sorted

/*Structure called option which contains information
about the performance of the sorting method as well as
general metadata used by other functionality*/
struct Option{
    std::string name; //Indicates the name of the sorting method
    int id; //Associates an id with the sorting method
    //Counters for the number of array accesses and data moves performed by the sorting method
    uint64_t access_count{}, move_count{}; 
    std::chrono::duration<double> time; //Variable to store the time taken to sort the list using a method

    Option() = default;

    explicit Option(int id){ //Constructor to create an option based on an id
        switch (id){
            case 0: //If id is 0, option is called compare
                this->name = "compare";
            case 1: //If id is 1, option is called selection sort
                this->name = "selection sort";
                break;
            case 2: //If id is 2, option is called bubble sort
                this->name = "bubble sort";
                break;
            case 3: //If id is 3, option is called insertion sort
                this->name = "insertion sort";
                break;
            case 4: //If id is 4, option is called quick sort
                this->name = "quick sort";
                break;
            case 5: //If id is 5, option is called merge sort
                this->name = "merge sort";
                break;
            default: //Else, option is called invalid
                this->name = "invalid";
        }

        this->id = id;
    }

    const Option& operator=(int id){ //Operator to allow assignment of options to integers
        return *this = Option(id); //Creates a new option given an id and assigns it to the caller
    }
};

//Abstraction to receive input from the user and format an option accordingly
void receive_input(Option& input){
    //Extract characters from the standard input stream and store them in the integer variable id
    int id;
    std::cin >> id;

    input = id; //Calls integer to option assignment operator

    //Error handling if the input stream fails to extract characters
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');

        input = -1;
    }
}

//Initialize an array of integers with random integers between low and high
void list_init(int low, int high, int (&list)[LIST_SIZE]){
    for (auto& x : list)
        x = (rand() % (high - low)) + low; //Generates a random number between low (inclusive) and high (exclusive)
}

//Using a vector of options, print a table containing information about the sorting methods compared.
void get_results(const std::vector<Option>& options){
    Option stats[6]; //Array of six option objects
    /*stats[0] for fastest time, stats[1] for lowest array access count, stats[2] for lowest data move count
    stats[3] for slowest time, stats[4] for highest array access count, stats[5] for highest data move count*/
    for (int i = 0; i < 6; ++i)
        stats[i] = options[0]; //Initialize array of six options

    //Cycle through list of options and compare to current stats stored
    for (int i = 1; i < options.size(); ++i){
        if (options[i].time < stats[0].time)
            stats[0] = options[i]; //If lower time is found, update stats[0]

        if (options[i].access_count < stats[1].access_count)
            stats[1] = options[i]; //If lower access count found, update stats[1]

        if (options[i].move_count < stats[2].move_count)
            stats[2] = options[i]; //If lower move count found, update stats[2]

        if (options[i].time > stats[3].time)
            stats[3] = options[i]; //If higher time found, update stats[3]

        if (options[i].access_count > stats[4].access_count)
            stats[4] = options[i]; //If higher access count found, update stats[4]

        if (options[i].move_count > stats[5].move_count)
            stats[5] = options[i]; //If higher move count found, updates stats[5]
    }

    //Display table of statistics calculated
    std::cout << "\n__RESULTS__\n";
    std::cout << "FASTEST TIME: {type: " << stats[0].name << "}, {time: " << stats[0].time.count() << "s}\n";
    std::cout << "LOWEST # OF ARRAY ACCESSES: {type: " << stats[1].name << "}, {accesses: " << stats[1].access_count << "}\n";
    std::cout << "LOWEST # OF DATA MOVES: {type: " << stats[2].name << "}, {moves: " << stats[2].move_count << "}\n\n";

    std::cout << "SLOWEST TIME: {type: " << stats[3].name << "}, {time: " << stats[3].time.count() << "s}\n";
    std::cout << "HIGHEST # OF ARRAY ACCESS: {type: " << stats[4].name << "}, {accesses: " << stats[4].access_count << "}\n";
    std::cout << "HIGHEST # OF DATA MOVES: {type: " << stats[5].name << "}, {moves: " << stats[5].move_count << "}\n\n";
}

//Run the chosen sorting methods and collect statistics such as time taken, array access count, data move count
void compare_options(std::vector<Option>& options){
    int list[LIST_SIZE], copy_list[LIST_SIZE]; //Create two lists of size 50,000 to hold the data

    std::chrono::time_point<std::chrono::system_clock> start_time, end_time; //Create a start and stop time variable to time the sorting algorithms

    list_init(-25000, 25000, list); //Initialize the first list created with random numbers between -25,000 and 25,000
    memcpy(copy_list, list, sizeof(list)); //Perform a byte-wise copy on the first list into the copy list

    std::endl(std::cout);
    std::cout << "__SORTING DATA (1s delay)__\n";
    //Loop through list of options and execute each one
    for (auto& option : options){
        std::pair<uint64_t, uint64_t> results;

        start_time = std::chrono::system_clock::now(); //Get algorithm start time
        //Switch statement to choose which algorithm to execute based on the current option in the option list
        switch (option.id){
            case 1:
                algo::selection_sort(list, LIST_SIZE, results); //Execute selection sort
                break;
            case 2:
                algo::bubble_sort(list, LIST_SIZE, results); //Execute bubble sort
                break;
            case 3:
                algo::insertion_sort(list, LIST_SIZE, results); //Execute insertion sort
                break;
            case 4:
                algo::quick_sort(list, 0, LIST_SIZE - 1, results); //Execute quick sort
                break;
            case 5:
                algo::merge_sort(list, 0, LIST_SIZE - 1, results); //Execute merge sort
                break;
        }
        end_time = std::chrono::system_clock::now(); //Get algorithm finish time

        //Add metadata collected to option data members
        option.access_count = results.first;
        option.move_count = results.second;
        option.time = end_time - start_time;

        //Print metadata about sorting algorithm
        std::cout << "Sorting 50,000 integers (-25,000 <=> 25,000) {type: " << option.name << 
            "}, {id: " << option.id << "} took " << option.time.count() << "s to sort the list, " 
            << option.access_count << " array accesses, " << option.move_count << " data moves...\n";
        
        memcpy(list, copy_list, sizeof(list)); /*Perform a byte-wise copy on the copy list into the original list ,
        so the unsorted data can remain constant throughout each test*/

        std::this_thread::sleep_for(std::chrono::seconds(1)); //Pause the thread of execution for one second, so the metadata can be viewed more easily
    }
    std::endl(std::cout);

    get_results(options); //Call get_results() and print a table of notable statistics about all the trials
}

//Interface/menu for the user to choose the sorting methods to be compared
int get_options(std::vector<Option>& options){
    Option option(-1); //Create a new options object
    constexpr int num_options = 5; //Constant representing the number of sorting algorithms to choose from

    //Requests the user to enter a number 0 through 5 so it may pass the execution to the comparing segment
    std::cout << "\nPlease add a sorting algorithm (1-" << num_options << "), press (0) to compare, or anything else to exit...\n";
    std::cout << "Currently selected:\n";
    if (options.size() > 0){
        for (auto& x : options){
            std::cout << "=> {type: " << x.name << "}, {id: " << x.id << "}\n";
        }
    }
    else
        std::cout << "=> None\n";

    std::cout << "\n__Menu__\n";
    std::cout << "0 - Compare\n";
    std::cout << "1 - Selection sort\n";
    std::cout << "2 - Bubble sort\n";
    std::cout << "3 - Insertion sort\n";
    std::cout << "4 - Quick sort\n";
    std::cout << "5 - Merge sort\n";

    //Loops until the user enters a number not on the menu, such as -5 or the letter 'k'
    do{
        bool removed = false;
        receive_input(option); //Call the input function to extract characters from the input stream and configure the option

        //If the option's id is greater than 0 and less than 5, either add the option to the option list or remove it if already present
        if (option.id > 0 && option.id <= num_options){
            int count{};

            //Loops through the options and removes the current chosen option if in the list
            for (auto& x : options){
                if (x.id == option.id){
                    options.erase(options.begin() + count);
                    std::cout << "[ Removed option {type: " << option.name << "}, {id: " << option.id << "} from comparison ]\n";
                    removed = true;
                } 

                ++count;
            }

            //If nothing was removed from the list, add the option to the options list
            if (!removed)
            {
                options.push_back(option);
                std::cout << "[ Added option {type: " << option.name << "}, {id: " << option.id << "} to comparison ]\n";
            } 
        }
        //Else if the option's id is equal to 0, exit the function and return control to the main function if there are more than two options selected
        else if (option.id == 0){
            if (options.size() < 2){ //If less than two options are selected, alert the user and set option to 1 so the loop continues
                std::cout << "Must have at least two options selected to compare!\n";
                option = 1;
            }
        }
        //Else if the option's id is greater than 0 as well as 5 in this case, alert the user that the option number is invalid
        else if (option.id > 0){
            std::cout << "Option number must be in the range of (1-" << num_options << ")!\n";
        }
        else return 0; //Return 0 if invalid input and return control to main function
    } while(option.id > 0);

    return 1; //If everything suceeds, return 1 and return control to the main function
}

int main(){
    srand(time(NULL)); //Initialize random class with the current system time seed for realistic random number generation

    std::vector<Option> options; //Vector of Options to store the list of options
    char input; //Input variable to store a character for yes/no questions
    
    //Loop comparing sorting algorithms until the user says they don't want to (N)
    do{
        if (get_options(options)){ //Get sorting algorithms and push them to the options list. Execute the list if anything but zero is returned, meaning success
            do{
                compare_options(options); //Run the chosen options/sorting algorithms and compare them

                //Request if the user would like to run the test again with the same sorting styles
                std::cout << "Would you like to compare these sorting styles again? (y/N)\n";
                std::cin >> input;
            } while(tolower(input) == 'y');
        }

        //Request if the user would like to quit the application
        std::cout << "Would you like to quit the application? (Y/n)\n";
        std::cin >> input;
    } while (tolower(input) == 'n');

    //If the user wants to quit the application, continue to the end of main() where the program will exit naturally
    std::cout << "Quitting program in... ";
    for (int i = 3; i > 0; --i){
        std::cout << i << ' ';
        std::this_thread::sleep_for(std::chrono::seconds(1)); //Pause the current thread of execution for three seconds, while printing a countdown in between each pause
    }
}