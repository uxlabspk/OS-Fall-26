
// Mutex Lock (slide 13)

#include <iostream>
#include <thread>
#include <mutex>
int counter = 0;
std::mutex m;

void add() {
    for (int i = 0; i < 100000; i++) {
        m.lock();
        counter++;          // critical section
        m.unlock();
    }
}

int main() {
    std::thread t1(add), t2(add);
    t1.join(); t2.join();
    std::cout << "Counter = " << counter << "\n";  // always 200000
    return 0;
}