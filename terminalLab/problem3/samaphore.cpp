#include <iostream>
#include <thread>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

// Define the semaphores
sem_t *semA;
sem_t *semB;

void printA() {
    for (int i = 0; i < 3; ++i) {
        sem_wait(semA);
        std::cout << "AAA";
        sem_post(semB);
    }
}

void printB() {
    for (int i = 0; i < 3; ++i) {
        sem_wait(semB);
        std::cout << "BBB";
        sem_post(semA);
    }
}

int main() {
    semA = sem_open("/semA", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
    semB = sem_open("/semB", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);

    std::thread threadA(printA);
    std::thread threadB(printB);
    threadA.join();
    threadB.join();

    sem_unlink("/semA");
    sem_unlink("/semB");

    return 0;
}
