

// Counting Semaphore: 3 Printers (slide 16)


#include <iostream>
#include <thread>
#include <semaphore>
#include <ctime>
std::counting_semaphore<3> printers(3);   // 3 printers available

void usePrinter(int id) {
    printers.acquire();                    // wait()
    std::cout << "Job " << id << " printing...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Job " << id << " done\n";
    printers.release();                    // signal()
}

int main() {
    std::thread jobs[5];                   // 5 jobs, only 3 print at once
    for (int i = 0; i < 5; i++) jobs[i] = std::thread(usePrinter, i + 1);
    for (auto& t : jobs) t.join();

    return 0;
}