//
// Created by muhammad on 19/10/2026.
//
#include <iostream>
#include <vector>
#include <deque>

struct Process {
    int id, remaining;
};

int main() {
    std::vector<Process> processes = {
        {1, 10}, {2, 4}, {3, 20}
    };

    std::deque<Process> q0, q1, q2;
    for (const auto& p : processes) {
        q0.push_back(p);
    }

    int currentTime = 0;

    auto run = [&](std::deque<Process>& current,
                   std::deque<Process>& next,
                   int quantum,
                   const std::string& level) {
        std::deque<Process> temp;

        while (!current.empty()) {
            Process p = current.front();
            current.pop_front();

            int runTime = std::min(quantum, p.remaining);
            p.remaining -= runTime;
            currentTime += runTime;

            std::cout << level << ": P" << p.id
                      << " runs " << runTime
                      << " units; remaining = "
                      << p.remaining << '\n';

            if (p.remaining > 0) {
                temp.push_back(p);
            }
        }

        next.insert(next.end(), temp.begin(), temp.end());
    };

    run(q0, q1, 4, "Queue 0");
    run(q1, q2, 8, "Queue 1");

    while (!q2.empty()) {
        Process p = q2.front();
        q2.pop_front();

        std::cout << "Queue 2 FCFS: P" << p.id
                  << " runs from " << currentTime
                  << " to " << currentTime + p.remaining << '\n';

        currentTime += p.remaining;
    }
}