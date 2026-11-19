
// Readers–Writers — reader priority with pthreads-style code (slides 28–29)

#include <iostream>
#include <thread>
#include <mutex>
std::mutex rw_mutex;   // protects the "database"
std::mutex count_mutex;
int read_count = 0;
int database = 0;

void writer(int id) {
    rw_mutex.lock();
    database = id * 10;                  // exclusive write
    std::cout << "Writer " << id << " wrote " << database << "\n";
    rw_mutex.unlock();
}

void reader(int id) {
    count_mutex.lock();
    read_count++;
    if (read_count == 1) rw_mutex.lock();  // first reader locks writers out
    count_mutex.unlock();

    std::cout << "Reader " << id << " read " << database << "\n";

    count_mutex.lock();
    read_count--;
    if (read_count == 0) rw_mutex.unlock(); // last reader lets writers in
    count_mutex.unlock();
}

int main() {
    std::thread w1(writer, 1);
    std::thread r1(reader, 1), r2(reader, 2), r3(reader, 3);
    std::thread w2(writer, 2);
    w1.join(); r1.join(); r2.join(); r3.join(); w2.join();
    return 0;
}