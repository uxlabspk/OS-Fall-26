#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        cout << "exiting the child process" << endl;
        cout << getpid() << endl;
        exit(0);
    } else {
        sleep(3);
        cout << "parent exiting without waiting..." << endl;
    }


    return 0;
}