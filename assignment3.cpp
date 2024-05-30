#include<iostream>
#include <pthread.h>
using namespace std;

#define matrix 4
#define totalThreads 3

int arr1[matrix][matrix] = 
{1,2,3,4,
  5,6,7,8,
  9,10,11,12,
  13,14,15,16
};
int arr2[matrix][matrix] = 
{1,2,3,4,
  5,6,7,8,
  9,10,11,12,
  13,14,15,16
};

int result[matrix][matrix];

void multiplyArrays(int initial_variable);
void *threadFunction(void *arg);

int main() {
    pthread_t threads[totalThreads];

    for (long i = 0; i < totalThreads; ++i) {
        pthread_create(&threads[i], NULL, threadFunction, (void *)i);
    }

    for (long i = 0; i < totalThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Resultant Matrix:\n");
    for (int i = 0; i < matrix; ++i) {
        for (int j = 0; j < matrix; ++j) {
            cout << result[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}

void multiplyArrays(int initial_variable){
  for (int i = initial_variable; i < initial_variable + 2; ++i) {
        for (int j = 0; j < matrix; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < matrix; ++k) {
                result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
}

void *threadFunction(void *arg) {
    long tid = (long)arg;
    // cout <<"The tId is: "<<tid << "\n";
    int row_start = tid * 2;
    multiplyArrays(row_start);
    pthread_exit(NULL);
}