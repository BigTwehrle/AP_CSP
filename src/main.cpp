#include <iostream>
#include <time.h>
#include <vector>
#include <limits>
#include <thread>
#include <chrono>
#include "algo.hpp"

#define LIST_SIZE 10000

struct Option{
    std::string name;
    int id;
    int iter_count{}, swap_count{};
    std::chrono::duration<double> time;

    explicit Option(int id){
        switch (id){
            case 0:
                this->name = "compare";
                this->id = id;
            case 1:
                this->name = "selection sort";
                this->id = id;
                break;
            case 2:
                this->name = "bubble sort";
                this->id = id;
                break;
            case 3:
                this->name = "insertion sort";
                this->id = id;
                break;
            case 4:
                this->name = "quick sort";
                this->id = id;
                break;
            case 5:
                this->name = "merge sort";
                this->id = id;
                break;
            default:
                this->name = "invalid";
                this->id = id;
        }
    }

    const Option& operator=(int id){
        switch (id){
            case 0:
                this->name = "compare";
                this->id = id;
            case 1:
                this->name = "selection sort";
                this->id = id;
                break;
            case 2:
                this->name = "bubble sort";
                this->id = id;
                break;
            case 3:
                this->name = "insertion sort";
                this->id = id;
                break;
            case 4:
                this->name = "quick sort";
                this->id = id;
                break;
            case 5:
                this->name = "merge sort";
                this->id = id;
                break;
            default:
                this->name = "invalid";
                this->id = id;
        }

        return *this;
    }
};

void receive_input(Option& input){
    int id;
    std::cin >> id;

    input = id;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');

        input = -1;
    }
}

void list_init(int low, int high, int (&list)[LIST_SIZE]){
    for (auto& x : list)
        x = (rand() % (high - low)) + low;
}

void get_results(const std::vector<Option>& options){
    Option min_options[3] {options[0], options[0], options[0]};

    for (int i = 1; i < options.size(); ++i){
        if (options[i].time < min_options[0].time)
            min_options[0] = options[i];

        if (options[i].iter_count < min_options[1].iter_count)
            min_options[1] = options[i];

        if (options[i].swap_count < min_options[2].swap_count)
            min_options[2] = options[i];
    }

    std::cout << "\n__RESULTS__\n";
    std::cout << "FASTEST TIME: {type: " << min_options[0].name << "}, {time: " << min_options[0].time.count() << "s}\n";
    std::cout << "LOWEST # OF ITERATIONS: {type: " << min_options[1].name << "}, {iterations: " << min_options[1].iter_count << "}\n";
    std::cout << "LOWEST # OF SWAPS: {type: " << min_options[2].name << "}, {swaps: " << min_options[2].swap_count << "}\n\n";
}

void compare_options(std::vector<Option>& options){
    int list[LIST_SIZE], copy_list[LIST_SIZE];

    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;

    list_init(-1000, 1000, list);
    memcpy(copy_list, list, sizeof(list));

    std::endl(std::cout);
    std::cout << "__SORTING DATA (1s delay)__\n";
    for (auto& option : options){
        std::pair<int, int> results;

        // for (auto& x : list)
        //     std::cout << x << ' ';
        // std::endl(std::cout);

        start_time = std::chrono::system_clock::now();
        switch (option.id){
            case 1:
                algo::selection_sort(list, LIST_SIZE, results);
                break;
            case 2:
                algo::bubble_sort(list, LIST_SIZE, results);
                break;
            case 3:
                algo::insertion_sort(list, LIST_SIZE, results);
                break;
            case 4:
                algo::quick_sort(list, 0, LIST_SIZE - 1, results);
                break;
        }
        end_time = std::chrono::system_clock::now();

        // for (auto& x : list)
        //     std::cout << x << ' ';
        // std::endl(std::cout);

        option.iter_count = results.first;
        option.swap_count = results.second;
        option.time = end_time - start_time;

        std::cout << "Sorting {type: " << option.name << "}, {id: " << option.id << "} took " << option.time.count() << "s to sort the list, " 
        << option.iter_count << " iterations, " << option.swap_count << " swaps...\n";

        memcpy(list, copy_list, sizeof(list));

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::endl(std::cout);

    get_results(options);
}

int get_options(std::vector<Option>& options){
    Option option(-1);
    int num_options = 5;

    std::cout << "\nPlease add a sorting algorithm (1-" << num_options << ", press (0) to compare, or anything else to exit...\n";
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
    std::cout << "5 - Merge sort\n\n";

    do{
        bool removed = false;
        receive_input(option); 

        if (option.id > 0 && option.id <= num_options){
            int count{};

            for (auto& x : options){
                if (x.id == option.id){
                    options.erase(options.begin() + count);
                    std::cout << "[ Removed option {type: " << option.name << "}, {id: " << option.id << "} from comparison ]\n";
                    removed = true;
                } 

                ++count;
            }

            if (!removed)
            {
                options.push_back(option);
                std::cout << "[ Added option {type: " << option.name << "}, {id: " << option.id << "} to comparison ]\n";
            } 
        }
        else if (option.id == 0){
            if (options.size() < 2){
                std::cout << "Must have at least two options selected to compare!\n";
                option = 1;
            }
        }
        else if (option.id > 0){
            std::cout << "Option number must be in the range of (1-" << num_options << ")!\n";
        }
        else return 1;
    } while(option.id > 0);

    return 0;
}

int main(){
    srand(time(NULL));

    std::vector<Option> options;
    char input;
    
    do{
        if (!get_options(options)){
            do{
                compare_options(options);

                std::cout << "Would you like to compare these sorting styles again? (y/N)\n";
                std::cin >> input;
            } while(tolower(input) == 'y');
        }

        std::cout << "Would you like to quit the application? (Y/n)\n";
        std::cin >> input;
    } while (tolower(input) == 'n');

    std::cout << "Quitting program in... ";
    for (int i = 3; i > 0; --i){
        std::cout << i << ' ';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}