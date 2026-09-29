#include <iostream>
#include <sys/shm.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

#define SHM_SIZE 1024  // Bytes

// Bounded-buffer producer/consumer
int main() {
    // Create shared memory segment
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid == -1) {
        std::cerr << "shmget failed!" << std::endl;
        return 1;
    }

    // Attach to shared memory
    char* shmptr = (char*)shmat(shmid, NULL, 0);
    if (shmptr == (char*)-1) {
        std::cerr << "shmat failed!" << std::endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child: Write to shared memory
        strcpy(shmptr, "Hello from Shared Memory!");
        shmdt(shmptr); // Detach
    } else {
        // Parent: Wait and read
        wait(NULL);
        std::cout << "Parent read: " << shmptr << std::endl;

        // Clean up
        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}