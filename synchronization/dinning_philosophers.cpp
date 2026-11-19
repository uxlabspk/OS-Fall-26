

// Dining Philosophers (slides 31–33)
#include <iostream>
#include <thread>
#include <mutex>
std::mutex chopstick[5];

void philosopher(int i) {
    int left = i;
    int right = (i + 1) % 5;

    // Solution: last philosopher picks right first -> breaks deadlock
    if (i == 4) std::swap(left, right);

    chopstick[left].lock();
    chopstick[right].lock();
    std::cout << "Philosopher " << i << " is eating\n";
    chopstick[right].unlock();
    chopstick[left].unlock();
}

int main() {
    std::thread p[5];
    for (int i = 0; i < 5; i++) p[i] = std::thread(philosopher, i);
    for (auto& t : p) t.join();

    return 0;
}