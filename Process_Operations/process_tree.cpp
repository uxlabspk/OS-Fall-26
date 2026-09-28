#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

void printProcessInfo(const std::string& label) {
    std::cout << label << ": PID = " << getpid() << ", PPID = " << getppid() << std::endl;
}

int main() {
    pid_t pid1 = fork(); // First child
    if (pid1 == 0) {
        printProcessInfo("Child 1");
        pid_t pid2 = fork(); // Child 1 creates Child 2
        if (pid2 == 0) {
            printProcessInfo("Child 2");
        } else {
            wait(NULL); // Child 1 waits for Child 2
        }
    } else {
        pid_t pid3 = fork(); // Parent creates Child 3
        if (pid3 == 0) {
            printProcessInfo("Child 3");
        } else {
            wait(NULL); // Parent waits for Child 1 and Child 3
            printProcessInfo("Parent");
        }
    }
    return 0;
}