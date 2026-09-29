#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    // Create FIFO (named pipe)
    mkfifo("/tmp/FIFO", 0666); // Permissions: rw-rw-rw-

    const int fd = open("/tmp/FIFO", O_WRONLY);
    const char* msg = "Sending Message...";
    write(fd, msg, 18);
    close(fd);

    // Clean up (optional)
    unlink("/tmp/FIFO");
    return 0;
}