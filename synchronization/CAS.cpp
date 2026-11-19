
// Atomic / CAS (slides 9–11)

#include <iostream>
#include <thread>
#include <atomic>
std::atomic<int> counter = 0;

void add() {
    for (int i = 0; i < 100000; i++)
        counter++;   // atomic increment, same as CAS-based update
}

int main() {
    std::thread t1(add), t2(add);
    t1.join(); t2.join();
    std::cout << "Counter = " << counter << "\n";

    // Compare-and-Swap demo
    int value = 10;
    int expected = 10;
    counter.compare_exchange_strong(expected, 20);  // sets counter = 20 if old == 10
    std::cout << "After CAS: " << counter << "\n";   // prints 20

    return 0;
}