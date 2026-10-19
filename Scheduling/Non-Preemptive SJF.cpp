//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id, arrival, burst;
    bool done = false;
};

int main() {
    std::vector<Process> p = {
        {1, 0, 7}, {2, 2, 4}, {3, 4, 1}, {4, 5, 4}
    };

    int currentTime = 0, completed = 0;
    double totalWaiting = 0, totalTurnaround = 0;

    std::cout << "PID\tStart\tFinish\tWaiting\tTurnaround\n";

    while (completed < static_cast<int>(p.size())) {
        int idx = -1;

        for (int i = 0; i < static_cast<int>(p.size()); ++i) {
            if (!p[i].done && p[i].arrival <= currentTime) {
                if (idx == -1 || p[i].burst < p[idx].burst) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            ++currentTime;
            continue;
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

        std::cout << p[idx].id << '\t' << start << '\t'
                  << finish << '\t' << waiting << '\t'
                  << turnaround << '\n';
    }

    std::cout << "Average waiting time: "
              << totalWaiting / p.size() << '\n';
}