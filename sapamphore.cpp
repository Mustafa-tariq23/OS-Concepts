#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t semA;

void * funcA(void * arg){
    cout<<"A ";
    sem_post(&semA);
    return NULL;
}

void *processB (void * arg) {
    sem_wait(&semA); // Wait for Process A to signal
    cout << "B ";
    return NULL;
}
int main() {
sem_init(&semA, 0, 0);
pthread_t a,b;
pthread_create(&a,NULL,funcA,NULL);
pthread_create(&b,NULL,processB,NULL);
pthread_join(a,NULL);
pthread_join(b,NULL);
return 0;
}