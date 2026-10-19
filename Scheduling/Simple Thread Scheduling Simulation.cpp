//
// Created by muhammad on 19/10/2026.
//

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

class RoundRobinScheduler {
    std::queue<int> tasks;
    std::mutex m;
    std::condition_variable cv;
    bool finished = false;

public:
    void addTask(int id) {
        std::lock_guard<std::mutex> lock(m);
        tasks.push(id);
        cv.notify_one();
    }

    void runWorker(int workerId) {
        while (true) {
            std::unique_lock<std::mutex> lock(m);

            cv.wait(lock, [&] {
                return !tasks.empty() || finished;
            });

            if (tasks.empty() && finished) return;

            int task = tasks.front();
            tasks.pop();
            lock.unlock();

            std::cout << "Worker " << workerId
                      << " executing task " << task << '\n';

            std::this_thread::sleep_for(
                std::chrono::milliseconds(100));
        }
    }

    void finish() {
        std::lock_guard<std::mutex> lock(m);
        finished = true;
        cv.notify_all();
    }
};

int main() {
    RoundRobinScheduler scheduler;

    std::vector<std::thread> workers;
    for (int i = 1; i <= 2; ++i) {
        workers.emplace_back(&RoundRobinScheduler::runWorker,
                             &scheduler, i);
    }

    for (int task = 1; task <= 6; ++task) {
        scheduler.addTask(task);
    }

    scheduler.finish();

    for (auto& t : workers) {
        t.join();
    }
}