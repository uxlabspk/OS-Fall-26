#include <iostream>
#include <pthread.h>
#include <unistd.h>

void* printMessage(void* arg) {
    char* message = (char*)arg;
    std::cout << message << std::endl;
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char* msg1 = (char*)"Thread 1: Hello!";
    char* msg2 = (char*)"Thread 2: World!";

    // Create threads
    pthread_create(&thread1, NULL, printMessage, (void*)msg1);
    pthread_create(&thread2, NULL, printMessage, (void*)msg2);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    std::cout << "Main thread exiting." << std::endl;
    return 0;
}

// g++ pthread_example.cpp -o pthread_example -lpthread
// ./pthread_example