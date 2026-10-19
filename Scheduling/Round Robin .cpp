//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>
#include <queue>

struct Process {
    int id, arrival, burst, remaining;
};

int main() {
    std::vector<Process> p = {
        {1, 0, 10, 10}, {2, 1, 5, 5}, {3, 2, 8, 8}
    };
    int quantum = 3;

    std::queue<int> ready;
    for (int i = 0; i < static_cast<int>(p.size()); ++i) {
        ready.push(i);
    }

    int currentTime = 0;
    double totalWaiting = 0, totalTurnaround = 0;
    std::vector<int> finishTime(p.size());

    while (!ready.empty()) {
        int i = ready.front();
        ready.pop();

        int run = std::min(quantum, p[i].remaining);
        p[i].remaining -= run;
        currentTime += run;

        if (p[i].remaining > 0) {
            ready.push(i);
        } else {
            finishTime[i] = currentTime;
        }
    }

    std::cout << "PID\tFinish\tWaiting\tTurnaround\n";

    for (int i = 0; i < static_cast<int>(p.size()); ++i) {
        int turnaround = finishTime[i] - p[i].arrival;
        int waiting = turnaround - p[i].burst;

        totalWaiting += waiting;
        totalTurnaround += turnaround;

        std::cout << p[i].id << '\t' << finishTime[i] << '\t'
                  << waiting << '\t' << turnaround << '\n';
    }

    std::cout << "Average waiting time: "
              << totalWaiting / p.size() << '\n';
}