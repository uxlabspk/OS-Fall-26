#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    const pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork Failed" << std::endl;
        return -1;
    }

    if (pid == 0) {
        // execl("/bin/ls", "ls", "-l", NULL);
        // execlp("ls", "ls", "-l", NULL);


        char* argv[] = {"ls", "-l", nullptr};
        execv("/bin/ls", argv);
        execvp("ls", argv);

        // char* argv[] = {"ls", "-l", nullptr};
        // execv("/bin/ls", argv);

        // char* argv[] = {"ls", "-l", nullptr};
        // execvp("ls", argv);

        // char* envp[] = {"PATH=/bin", "USER=muhammad", NULL};
        // execle("/bin/ls", "ls", "-l", NULL, envp);

        return 0;
    }

    wait(nullptr);
    std::cout << "Process Id (PID) : " << getpid() << std::endl;

    return 0;
}