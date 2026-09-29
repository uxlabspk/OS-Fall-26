#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2]; // fd[0] = read, fd[1] = write

    if (pipe(fd) < 0) {
        std::cerr << "Pipe failed!" << std::endl;
        return 1;
    }

    const pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid == 0) {
        // Child: Write to pipe
        close(fd[0]); // Close read end
        const char* msg = "Hello from child!";
        std::cout << "Writing mesage" << std::endl;
        write(fd[1], msg, 18);
        close(fd[1]);
    } else {
        // Parent: Read from pipe
        close(fd[1]); // Close write end
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        std::cout << "Parent received: " << buffer << std::endl;
        close(fd[0]);
        wait(nullptr); // Wait for child
    }
    return 0;
}