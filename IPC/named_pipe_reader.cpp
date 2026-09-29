#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("/tmp/FIFO", O_RDONLY);
    char buffer[100];
    read(fd, buffer, sizeof(buffer));
    std::cout << "Reader received: " << buffer << std::endl;
    close(fd);
    return 0;
}