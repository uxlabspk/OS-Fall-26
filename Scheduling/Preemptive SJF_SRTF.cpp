//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id, arrival, burst, remaining;
};

int main() {
    std::vector<Process> p = {
        {1, 0, 8, 8}, {2, 1, 4, 4},
        {3, 2, 9, 9}, {4, 3, 5, 5}
    };

    int currentTime = 0, completed = 0;
    double totalWaiting = 0, totalTurnaround = 0;

    while (completed < static_cast<int>(p.size())) {
        int idx = -1;

        for (int i = 0; i < static_cast<int>(p.size()); ++i) {
            if (p[i].arrival <= currentTime && p[i].remaining > 0) {
                if (idx == -1 || p[i].remaining < p[idx].remaining) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            ++currentTime;
            continue;
        }

        --p[idx].remaining; // runs for 1 time unit
        ++currentTime;

        if (p[idx].remaining == 0) {
            int finish = currentTime;
            int turnaround = finish - p[idx].arrival;
            int waiting = turnaround - p[idx].burst;

            totalTurnaround += turnaround;
            totalWaiting += waiting;
            ++completed;

            std::cout << "P" << p[idx].id
                      << " finished at " << finish
                      << ", waiting = " << waiting
                      << ", turnaround = " << turnaround << '\n';
        }
    }

    std::cout << "Average waiting time: "
              << totalWaiting / p.size() << '\n';
    std::cout << "Average turnaround time: "
              << totalTurnaround / p.size() << '\n';
}