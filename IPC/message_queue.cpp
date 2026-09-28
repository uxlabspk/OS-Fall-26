#include <iostream>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#define MSGQ_KEY 1234

struct Message {
    long mtype;    // Message type (must be > 0)
    char mtext[100]; // Message content
};

int main() {
    // Create message queue
    int msgid = msgget(MSGQ_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        std::cerr << "msgget failed!" << std::endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child: Send message
        Message msg;
        msg.mtype = 1;
        strcpy(msg.mtext, "Hello via Message Queue!");
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
        std::cout << "Child sent message." << std::endl;
    } else {
        // Parent: Receive message
        Message msg;
        msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0);
        std::cout << "Parent received: " << msg.mtext << std::endl;

        // Clean up
        msgctl(msgid, IPC_RMID, NULL);
        wait(NULL);
    }
    return 0;
}