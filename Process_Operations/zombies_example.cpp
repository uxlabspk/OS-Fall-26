#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    const pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork Failed" << endl;
        return -1;
    }

    if (pid == 0) {
        cout << "This is child process with PID : " << getpid() << endl;
        exit(0);
    } else {
        sleep(3);
        cout << "parent exiting without waiting..." << endl;
    }


    return 0;
}