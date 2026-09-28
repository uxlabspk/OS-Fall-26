#include <iostream>
#include <thread>

thread_local int thread_id = 0; // Each thread has its own copy

void printThreadId() {
    thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    std::cout << "Thread " << thread_id << ": ID = " << thread_id << std::endl;
}

int main() {
    std::thread t1(printThreadId);
    std::thread t2(printThreadId);

    t1.join();
    t2.join();

    return 0;
}