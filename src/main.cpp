#include <iostream>
#include <time.h>

unsigned int list[1000];

void menu(){
    std::cout << "Please select a sorting algorithm:\n";
}

void list_init(unsigned int low, unsigned int high){
    for (auto& x : list)
        x = (rand() % (high - low)) + low;
}

void print_list(){
    for (auto& x : list)
        std::cout << x << ' ';
    std::endl(std::cout);
}

int main(){
    srand(time(NULL));

    list_init(5, 10);
    print_list();
}