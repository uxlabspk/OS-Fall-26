#include <iostream>
#include <cstring>
#include <fcntl.h>      // O_CREAT, O_RDWR
#include <sys/mman.h>   // shm_open, mmap
#include <sys/stat.h>   // mode constants
#include <unistd.h>     // ftruncate, close
using namespace std;

int main() {
    const int SIZE = 4096;
    const char* name = "OS";
    const string message0 = "Hello ";
    const string message1 = "World!";

    // 1. Create the shared-memory object
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) { perror("shm_open"); return 1; }

    // 2. Set its size
    if (ftruncate(fd, SIZE) == -1) { perror("ftruncate"); return 1; }

    // 3. Map it into this process's address space
    char* ptr = (char*) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) { perror("mmap"); return 1; }

    // 4. Write to shared memory
    memcpy(ptr, message0.c_str(), message0.size());
    ptr += message0.size();
    memcpy(ptr, message1.c_str(), message1.size() + 1);  // +1 for '\0'

    cout << "Producer: message written to shared memory\n";
    return 0;
}