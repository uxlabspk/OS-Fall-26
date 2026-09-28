#include <iostream>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child sleeps
        sleep(5);
        std::cout << "Child: PID = " << getpid() << ", PPID = " << getppid() << std::endl;
    } else {
        // Parent exits immediately (orphans the child)
        std::cout << "Parent exiting..." << std::endl;
    }
    return 0;
}