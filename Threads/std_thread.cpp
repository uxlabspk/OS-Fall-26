#include <iostream>
#include <thread>
#include <vector>

void printMessage(const std::string& message) {
    std::cout << message << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    std::vector<std::string> messages = {
        "Thread 1: Hello from C++11!",
        "Thread 2: std::thread is easier!",
        "Thread 3: No pthreads needed!"
    };

    // Create threads
    for (size_t i = 0; i < messages.size(); ++i) {
        threads.emplace_back(printMessage, messages[i]);
    }

    // Wait for all threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Main thread exiting." << std::endl;
    return 0;
}

// g++ -std=c++11 std_thread_example.cpp -o std_thread_example -pthread
// ./std_thread_example