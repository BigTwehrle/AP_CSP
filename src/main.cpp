#include <iostream>
#include <time.h>
#include <vector>
#include <limits>
#include <algorithm>
#include <thread>
#include <chrono>
#include "algo/algo.hpp"

struct Option{
    std::string opt_name;
    int opt_num;

    Option(int num){
        switch (num){
            case 0:
                this->opt_name = "compare";
                this->opt_num = num;
            case 1:
                this->opt_name = "selection sort";
                this->opt_num = num;
                break;
            case 2:
                this->opt_name = "buble sort";
                this->opt_num = num;
                break;
            default:
                this->opt_name = "invalid";
                this->opt_num = num;
        }
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
    int list[1000];

    std::cout << "Please input a range of data to sort between <low:high> -2147483648 and 2147483647:\n";
    int low, high;
    std::cin >> low >> high;

    list_init(low, high, list);

    print_list<1000>(list);

    algo::selection_sort(list, 1000);

    print_list<1000>(list);
}

void receive_input(int& input){
    std::cin >> input;

    if (std::cin.fail())
    {
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        std::cin.clear();

        input = -1;
    }
}

void get_options(std::vector<Option>& options){
    using const_it = std::vector<Option>::const_iterator;
    int input = -1;

    std::cout << "\nPlease add a sorting algorithm (1-2), press (0) to compare, or anything else to exit:\n";

    std::cout << "0 - Compare\n";
    std::cout << "1 - Selection sort\n";
    std::cout << "2 - Bubble sort\n\n";

    do{
        bool removed = false;
        receive_input(input);
        Option option(input); 

        if (option.opt_num > 0 && option.opt_num <= 2){
            for (const_it begin = options.begin(),
                end = options.end();
                begin != end;
                ++begin){
                if (begin->opt_num == option.opt_num){
                    std::cout << "[ Removed option name: " << option.opt_name << ", id: " << option.opt_num << " from comparison ]\n";
                    options.erase(begin);
                    removed = true;
                } 
            }

            if (!removed)
            {
                std::cout << "[ Added option name: " << option.opt_name << ", id: " << option.opt_num << " to comparison ]\n";
                options.push_back(option);
            } 
        }
        else if (option.opt_num == 0){
            if (options.size() < 2){
                std::cout << "Must have at least two options selected to compare!\n";
                input = 1;
            }
        }
        else{
            std::cout << "Option number must be in the range of (1-2)!\n";
        }
    } while(input > 0);

    if (input < 0){
        std::cout << "Qutting program in... ";

        for (int i = 3; i > 0; --i){
            std::cout << i << ' ';
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        exit(0);
    }
}

int main(){
    srand(time(NULL));

    std::vector<Option> options;
    
    get_options(options);

    compare(options);
}