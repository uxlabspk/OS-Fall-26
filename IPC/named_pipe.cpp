#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    // Create FIFO (named pipe)
    mkfifo("/tmp/myfifo", 0666); // Permissions: rw-rw-rw-

    int fd = open("/tmp/myfifo", O_WRONLY);
    const char* msg = "Hello via FIFO!";
    write(fd, msg, 15);
    close(fd);

    // Clean up (optional)
    unlink("/tmp/myfifo");
    return 0;
}