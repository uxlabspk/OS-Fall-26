//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>

struct Result {
    int id, arrival, burst, finish;
};

int main() {
    std::vector<Result> results = {
        {1, 0, 10, 10}, {2, 1, 5, 18}, {3, 2, 8, 26}
    };

    double totalWaiting = 0;
    double totalTurnaround = 0;
    int totalTime = 0;

    for (const auto& r : results) {
        int turnaround = r.finish - r.arrival;
        int waiting = turnaround - r.burst;

        totalTurnaround += turnaround;
        totalWaiting += waiting;
        totalTime = std::max(totalTime, r.finish);

        std::cout << "P" << r.id
                  << " waiting = " << waiting
                  << ", turnaround = " << turnaround << '\n';
    }

    double cpuUtilization = 100.0 *
        [&] {
            int busy = 0;
            for (const auto& r : results) busy += r.burst;
            return busy;
    }() / totalTime;

    std::cout << "CPU utilization: " << cpuUtilization << "%\n";
    std::cout << "Average waiting time: "
              << totalWaiting / results.size() << '\n';
    std::cout << "Average turnaround time: "
              << totalTurnaround / results.size() << '\n';
}