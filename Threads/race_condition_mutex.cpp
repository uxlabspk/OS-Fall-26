#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int counter = 0;
std::mutex mtx; // Mutex for synchronization

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();   // Lock before critical section
        counter++;
        mtx.unlock(); // Unlock after critical section
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(increment);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Counter: " << counter << std::endl; // Now correct: 400000
    return 0;
}