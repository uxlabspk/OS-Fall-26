#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    const pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork Failed" << std::endl;
        return 1;
    }

    if (pid == 0) {
        // execl("/bin/ls", "ls", "-l", NULL);

        // execlp("ls", "ls", "-l", NULL);

        // char* envp[] = {"PATH=/bin", "USER=muhammad", NULL};
        // execle("/bin/ls", "ls", "-l", NULL, envp);

        // char* argv[] = {"ls", "-l", NULL};
        // execv("/bin/ls", argv);

        return 0;
    }

    wait(nullptr);
    std::cout << "Process Id (PID) : " << getpid() << std::endl;

    return 0;
}