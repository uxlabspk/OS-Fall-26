//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>
#include <deque>

struct Process {
    int id, burst;
};

int main() {
    std::deque<Process> systemQueue = {{1, 2}, {2, 3}};
    std::deque<Process> interactiveQueue = {{3, 4}};
    std::deque<Process> batchQueue = {{4, 6}, {5, 2}};

    int currentTime = 0;

    auto runQueue = [&](std::deque<Process>& q, const std::string& name) {
        while (!q.empty()) {
            Process p = q.front();
            q.pop_front();

            std::cout << name << " process P" << p.id
                      << " runs from " << currentTime
                      << " to " << currentTime + p.burst << '\n';

            currentTime += p.burst;
        }
    };

    runQueue(systemQueue, "System");
    runQueue(interactiveQueue, "Interactive");
    runQueue(batchQueue, "Batch");
}