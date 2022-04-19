#include <iostream>
#include <time.h>
#include <vector>
#include <limits>
#include <algorithm>
#include <thread>
#include <chrono>
#include "algo/algo.hpp"

#define LIST_SIZE 10000

struct Option{
    std::string opt_name;
    int opt_id;

    enum class State{ Bad = 1, Good = 0 };

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
                this->opt_name = "buble sort";
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
                this->opt_name = "buble sort";
                this->opt_id = id;
                break;
            default:
                this->opt_name = "invalid";
                this->opt_id = id;
        }

        return *this;
    }
};

template <size_t S>
void list_init(int low, int high, int (&list)[S]){
    for (auto& x : list)
        x = (rand() % (high - low)) + low;
}

template <size_t S>
void print_list(int (&list)[S]){
    std::cout << "List contents: ";

    for (auto& x : list)
        std::cout << x << ' ';

    std::endl(std::cout);
}

void compare(const std::vector<Option>& options){
    int list[LIST_SIZE], copy_list[LIST_SIZE];

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    std::cout << "Please input a range of data to sort {low} {high} between -2147483648 and 2147483647:\n";
    int low, high;
    std::cin >> low >> high;

    list_init(low, high, list);
    memcpy(copy_list, list, sizeof(list));

    for (auto& x : options){
        switch (x.opt_id){
            case 1:
                start = std::chrono::system_clock::now();
                algo::selection_sort(list, LIST_SIZE);
                end = std::chrono::system_clock::now();
                break;
            case 2:
                start = std::chrono::system_clock::now();
                algo::bubble_sort(list, LIST_SIZE);
                end = std::chrono::system_clock::now();
                break;
        }

        elapsed_seconds = end - start;
        std::cout << "Sorting {type: " << x.opt_name << "}, {id: " << x.opt_id << "} took " << elapsed_seconds.count() << "s to sort the list\n";

       memcpy(list, copy_list, sizeof(list));
    }
}

void receive_input(Option& input){
    int id;
    std::cin >> id;

    input = id;

    if (std::cin.fail())
    {
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        std::cin.clear();

        input = -1;
    }
}

void get_options(std::vector<Option>& options){
    Option option(-1);

    std::cout << "\nPlease add a sorting algorithm (1-2), press (0) to compare, or anything else to exit:\n";

    std::cout << "0 - Compare\n";
    std::cout << "1 - Selection sort\n";
    std::cout << "2 - Bubble sort\n\n";

    do{
        bool removed = false;
        receive_input(option); 

        if (option.opt_id > 0 && option.opt_id <= 2){
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
        else if (option.opt_id < 0){
            std::cout << "Qutting program in... ";

            for (int i = 3; i > 0; --i){
                std::cout << i << ' ';
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            
            exit(0);
        }
        else if (option.opt_id == 0){
            if (options.size() < 2){
                std::cout << "Must have at least two options selected to compare!\n";
                option = 1;
            }
        }
        else{
            std::cout << "Option number must be in the range of (1-2)!\n";
        }
    } while(option.opt_id > 0);
}

int main(){
    srand(time(NULL));

    std::vector<Option> options;
    
    get_options(options);
    compare(options);
}