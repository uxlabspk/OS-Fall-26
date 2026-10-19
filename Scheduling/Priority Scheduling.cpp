//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id, arrival, burst, priority;
    bool done = false;
};

int main() {
    std::vector<Process> p = {
        {1, 0, 10, 3}, {2, 0, 1, 1},
        {3, 0, 2, 4}, {4, 0, 1, 5}, {5, 0, 5, 2}
    };

    int currentTime = 0, completed = 0;
    double totalWaiting = 0, totalTurnaround = 0;

    while (completed < static_cast<int>(p.size())) {
        int idx = -1;

        for (int i = 0; i < static_cast<int>(p.size()); ++i) {
            if (!p[i].done && p[i].arrival <= currentTime) {
                if (idx == -1 || p[i].priority < p[idx].priority) {
                    idx = i;
                }
            }
        }

        int start = currentTime;
        int finish = start + p[idx].burst;
        int waiting = start - p[idx].arrival;
        int turnaround = finish - p[idx].arrival;

        totalWaiting += waiting;
        totalTurnaround += turnaround;
        p[idx].done = true;
        currentTime = finish;
        ++completed;

        std::cout << "P" << p[idx].id
                  << " runs from " << start
                  << " to " << finish << '\n';
    }

    std::cout << "Average waiting time: "
              << totalWaiting / p.size() << '\n';
}