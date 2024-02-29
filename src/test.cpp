#include <iostream>
#include <random>
#include <thread>
#include <chrono>

int row_number;
int column_number;

void threadFunction() {   
    std::random_device rd;
    std::mt19937 gen(rd());
    
    while(true) {
        std::uniform_int_distribution<int> row(0, 31);
        std::uniform_int_distribution<int> column(0, 15);

        row_number = row(gen);
        column_number = column(gen);

        std::cout << "row : " << row_number << " column : " << column_number << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

int main() {
    std::thread t(threadFunction);
    t.join(); // Wait for the thread to finish (which will never happen in this case)
    return 0;
}
