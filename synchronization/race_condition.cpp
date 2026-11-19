

// Race Condition (slide 4)

#include <iostream>
#include <thread>
int counter = 0;

void add() {
    for (int i = 0; i < 100000; i++)
        counter++;   // race condition: result varies, some updates lost
}

int main() {
    std::thread t1(add), t2(add);
    t1.join(); t2.join();
    std::cout << "Counter = " << counter << " (expected 200000)\n";
    return 0;
}