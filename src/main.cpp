#include <iostream>
#include <time.h>
#include <vector>
#include <limits>
#include <algorithm>
#include <thread>
#include <chrono>

unsigned int list[1000];

void compare(const std::vector<int>& options){

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

void get_options(std::vector<int>& options){
    using const_it = std::vector<int>::const_iterator;
    int input = -1;

    std::cout << "\nPlease add a sorting algorithm (1-2), press (0) to compare, or anything else to exit:\n";

    std::cout << "0 - Compare\n";
    std::cout << "1 - Linear search\n";
    std::cout << "2 - Binary search\n\n";

    do{
        bool removed = false;
        receive_input(input);

        if (input <= 0) break;

        for (const_it begin = options.begin(),
            end = options.end();
            begin != end;
            ++begin){
                if (*begin == input){
                    std::cout << "[ Removed option " << *begin << " from comparison ]\n";
                    options.erase(begin);
                    removed = true;
                } 
            }

            if (!removed)
            {
                std::cout << "[ Added option " << input << " to comparison ]\n";
                options.push_back(input);
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

void list_init(unsigned int low, unsigned int high){
    for (auto& x : list)
        x = (rand() % (high - low)) + low;
}

void print_list(){
    std::cout << "List contents: ";

    for (auto& x : list)
        std::cout << x << ' ';

    std::endl(std::cout);
}

int main(){
    srand(time(NULL));

    std::vector<int> options;
    
    get_options(options);

    compare(options);
}