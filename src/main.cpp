#include <iostream>
#include <time.h>
#include <vector>
#include <limits>
#include <thread>
#include <chrono>
#include "algo.hpp"

#define LIST_SIZE 10000

struct Option{
    std::string opt_name;
    int opt_id;

    explicit Option(int id){
        switch (id){
            case 0:
                this->opt_name = "compare";
                this->opt_id = id;
            case 1:
                this->opt_name = "selection sort";
                this->opt_id = id;
                break;
            case 2:
                this->opt_name = "bubble sort";
                this->opt_id = id;
                break;
            case 3:
                this->opt_name = "insertion sort";
                this->opt_id = id;
                break;
            case 4:
                this->opt_name = "quick sort";
                this->opt_id = id;
                break;
            default:
                this->opt_name = "invalid";
                this->opt_id = id;
        }
    }

    const Option& operator=(int id){
        switch (id){
            case 0:
                this->opt_name = "compare";
                this->opt_id = id;
            case 1:
                this->opt_name = "selection sort";
                this->opt_id = id;
                break;
            case 2:
                this->opt_name = "bubble sort";
                this->opt_id = id;
                break;
            case 3:
                this->opt_name = "insertion sort";
                this->opt_id = id;
                break;
            case 4:
                this->opt_name = "quick sort";
                this->opt_id = id;
                break;
            default:
                this->opt_name = "invalid";
                this->opt_id = id;
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

void compare(const std::vector<Option>& options){
    int list[LIST_SIZE], copy_list[LIST_SIZE];

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    list_init(-1000, 1000, list);
    memcpy(copy_list, list, sizeof(list));

    std::endl(std::cout);
    for (auto& x : options){
        std::pair<int, int> results;

        // for (auto& x : list)
        //     std::cout << x << ' ';
        // std::endl(std::cout);

        start = std::chrono::system_clock::now();
        switch (x.opt_id){
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
        end = std::chrono::system_clock::now();

        // for (auto& x : list)
        //     std::cout << x << ' ';
        // std::endl(std::cout);

        elapsed_seconds = end - start;

        std::cout << "Sorting {type: " << x.opt_name << "}, {id: " << x.opt_id << "} took " << elapsed_seconds.count() << "s to sort the list, " 
        << results.first << " iterations, " << results.second << " swaps...\n";

        memcpy(list, copy_list, sizeof(list));
    }
    std::endl(std::cout);
}

int get_options(std::vector<Option>& options){
    Option option(-1);
    int num_options = 4;

    std::cout << "\nPlease add a sorting algorithm (1-" << num_options << ", press (0) to compare, or anything else to exit...\n";
    std::cout << "Currently selected:\n";
    if (options.size() > 0){
        for (auto& x : options){
            std::cout << "=> {type: " << x.opt_name << "}, {id: " << x.opt_id << "}\n";
        }
    }
    else
        std::cout << "=> None\n";

    std::cout << "\n__Menu__\n";
    std::cout << "0 - Compare\n";
    std::cout << "1 - Selection sort\n";
    std::cout << "2 - Bubble sort\n";
    std::cout << "3 - Insertion sort\n";
    std::cout << "4 - Quick sort\n\n";

    do{
        bool removed = false;
        receive_input(option); 

        if (option.opt_id > 0 && option.opt_id <= num_options){
            int count{};

            for (auto& x : options){
                if (x.opt_id == option.opt_id){
                    options.erase(options.begin() + count);
                    std::cout << "[ Removed option {type: " << option.opt_name << "}, {id: " << option.opt_id << "} from comparison ]\n";
                    removed = true;
                } 

                ++count;
            }

            if (!removed)
            {
                options.push_back(option);
                std::cout << "[ Added option {type: " << option.opt_name << "}, {id: " << option.opt_id << "} to comparison ]\n";
            } 
        }
        else if (option.opt_id == 0){
            if (options.size() < 2){
                std::cout << "Must have at least two options selected to compare!\n";
                option = 1;
            }
        }
        else if (option.opt_id > 0){
            std::cout << "Option number must be in the range of (1-" << num_options << ")!\n";
        }
        else return 1;
    } while(option.opt_id > 0);

    return 0;
}

int main(){
    srand(time(NULL));

    std::vector<Option> options;
    char input;
    
    do{
        if (!get_options(options)){
            do{
                compare(options);

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