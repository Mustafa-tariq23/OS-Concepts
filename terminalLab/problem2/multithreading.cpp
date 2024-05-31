#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

// Global variables to hold the results
int sumResult = 0;
double avgResult = 0.0;
int maxResult = 0;

// Structure to hold the execution sequence
struct ExecutionStruct {
    int threadId;
    string operation;
    double result;
};

// Array to hold the execution sequence and a counter
ExecutionStruct executionSequence[3];
int executionCounter = 0;

void* calculateSum(void* arg);

void* calculateAverage(void* arg);

void* calculateMaximum(void* arg);

int main() {
    int arr[5];

    // Input 5 integers
    cout << "Enter 5 integers: ";
    for (int i = 0; i < 5; ++i) {
        cin >> arr[i];
    }

    pthread_t threads[3];

    // Create threads
    pthread_create(&threads[0], NULL, calculateSum, (void*)arr);
    pthread_create(&threads[1], NULL, calculateAverage, (void*)arr);
    pthread_create(&threads[2], NULL, calculateMaximum, (void*)arr);

    // Wait for threads to complete
    for (int i = 0; i < 3; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Display the sequence of execution
    cout << "Execution sequence:" << endl;
    for (int i = 0; i < executionCounter; ++i) {
        const ExecutionStruct& record = executionSequence[i];
        cout << "Thread " << record.threadId << " (" << record.operation << ")" << endl;
    }

    // Display the results
    cout << "\nResults:" << endl;
    cout << "Sum: " << sumResult << endl;
    cout << "Average: " << avgResult << endl;
    cout << "Maximum: " << maxResult << endl;

    return 0;
}


// function initialization

// sum
void* calculateSum(void* arg) {
    int* arr = (int*)arg;
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += arr[i];
    }
    sumResult = sum;

    // Record execution
    executionSequence[executionCounter].threadId = 1;
    executionSequence[executionCounter].operation = "Sum";
    executionSequence[executionCounter].result = sum;
    executionCounter++;

    pthread_exit(NULL);
}

// average
void* calculateAverage(void* arg) {
    int* arr = (int*)arg;
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += arr[i];
    }
    double avg = sum / 5.0;
    avgResult = avg;

    // Record execution
    executionSequence[executionCounter].threadId = 2;
    executionSequence[executionCounter].operation = "Average";
    executionSequence[executionCounter].result = avg;
    executionCounter++;

    pthread_exit(NULL);
}


// max
void* calculateMaximum(void* arg) {
    int* arr = (int*)arg;
    int max = arr[0];
    for (int i = 1; i < 5; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    maxResult = max;

    // Record execution
    executionSequence[executionCounter].threadId = 3;
    executionSequence[executionCounter].operation = "Maximum";
    executionSequence[executionCounter].result = max;
    executionCounter++;

    pthread_exit(NULL);
}