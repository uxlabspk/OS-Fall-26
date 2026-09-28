//
// Created by muhammad on 28/09/2026.
//
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main() {
    const int SIZE = 4096;
    const char* name = "OS";

    // 1. Open the existing shared-memory object
    int fd = shm_open(name, O_RDONLY, 0666);
    if (fd == -1) { perror("shm_open (run producer first!)"); return 1; }

    // 2. Map it (read-only, since we only read)
    char* ptr = (char*) mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) { perror("mmap"); return 1; }

    // 3. Read and print
    cout << "Consumer read: " << ptr << "\n";

    // 4. Remove the shared-memory object
    shm_unlink(name);
    return 0;
}