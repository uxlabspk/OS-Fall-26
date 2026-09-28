#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    /*
     * In C++, pid_t is a dedicated data type used to
     * represent process identifiers (PIDs). It is
     * not a built-in feature of the core C++ language;
     * rather, it is defined by the POSIX standard
     * for Unix-like operating systems
     * (such as Linux and macOS) to manage system processes.
     */
    const pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "fork() failed" << std::endl;
        return 1;
    }

    if (pid == 0) {
        std::cout << "This is the child process" << std::endl;
        std::cout << "Process Id (PID) : " << getpid() << std::endl;
        std::cout << "Parent Process Id (PPID) : " << getppid() << std::endl;
    } else {
        wait(nullptr);
        std::cout << "This is the parent proces" << std::endl;
        std::cout << "Process Id (PID) : " << getpid() << std::endl;
        std::cout << "Parent Process Id (PID) : " << getppid() << std::endl;
    }

    return 0;
}