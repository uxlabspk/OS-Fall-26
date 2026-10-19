//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id, arrival, burst;
};

int main() {
    std::vector<Process> p = {
        {1, 0, 10}, {2, 1, 5}, {3, 2, 8}
    };

    std::sort(p.begin(), p.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival < b.arrival;
              });

    int currentTime = 0;
    double totalWaiting = 0, totalTurnaround = 0;

    std::cout << "PID\tStart\tFinish\tWaiting\tTurnaround\n";

    for (const auto& proc : p) {
        int start = std::max(currentTime, proc.arrival);
        int finish = start + proc.burst;
        int waiting = start - proc.arrival;
        int turnaround = finish - proc.arrival;

        totalWaiting += waiting;
        totalTurnaround += turnaround;

        std::cout << proc.id << '\t' << start << '\t'
                  << finish << '\t' << waiting << '\t'
                  << turnaround << '\n';

        currentTime = finish;
    }

    std::cout << "Average waiting time: "
              << totalWaiting / p.size() << '\n';
    std::cout << "Average turnaround time: "
              << totalTurnaround / p.size() << '\n';
}