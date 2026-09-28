#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;
const int MAX_SIZE = 5;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < MAX_SIZE; }); // Wait if buffer is full
        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;
        lock.unlock();
        cv.notify_one(); // Notify consumer
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); }); // Wait if buffer is empty
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << std::endl;
        lock.unlock();
        cv.notify_one(); // Notify producer
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}