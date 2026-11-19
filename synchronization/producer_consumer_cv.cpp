
//  Producer–Consumer with Condition Variable — bounded buffer (slides 19, 38)
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
std::queue<int> buffer;
const unsigned int CAPACITY = 3;
std::mutex m;
std::condition_variable cv;

void producer() {
    for (int item = 1; item <= 5; item++) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return buffer.size() < CAPACITY; }); // wait if full
        buffer.push(item);
        std::cout << "Produced " << item << "\n";
        lk.unlock();
        cv.notify_one();                                   // signal consumer
    }
}

void consumer() {
    for (int i = 0; i < 5; i++) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return !buffer.empty(); });          // wait if empty
        int item = buffer.front(); buffer.pop();
        std::cout << "Consumed " << item << "\n";
        lk.unlock();
        cv.notify_one();                                   // signal producer
    }
}

int main() {
    std::thread p(producer), c(consumer);
    p.join(); c.join();
    return 0;
}