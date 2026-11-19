

// Spinlock (slide 14)

#include <atomic>
#include <thread>
#include <iostream>
std::atomic<bool> lock = false;

void task() {
    // busy wait until lock is free, then grab it
    while (lock.exchange(true)) { }   // test-and-set style

    // critical section
    std::cout << "Thread " << std::this_thread::get_id() << " inside\n";
    // exit section
    lock = false;
}

int main() {
    std::thread t1(task), t2(task);
    t1.join(); t2.join();
    return 0;
}