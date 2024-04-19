#include <iostream>
#include <pthread.h>
using namespace std;

void* sum(void* arg);
void* product(void* arg);

int main(){
  pthread_t thread[2];

  int val[2] = {1,2};


  pthread_create(&thread[0], NULL, sum, (void*)val);
  pthread_join(thread[0], NULL);

  pthread_create(&thread[1], NULL, product, (void*)val);
  pthread_join(thread[1], NULL);

  return 0;
}

void* sum (void* arg){
  int* vals = (int*)arg;
  int val1 = vals[0];
  int val2 = vals[1];

  pthread_t tid = pthread_self();

  unsigned long int tid_int = (unsigned long int)tid;

  cout << "The sum is: " << val1 + val2 << endl;
  cout << "The thread id of this sum thread is: " << tid_int << endl << endl;

  return NULL;
}
void* product (void* arg){
  int* vals = (int*)arg;
  int val1 = vals[0];
  int val2 = vals[1];

   pthread_t tid = pthread_self();

  unsigned long int tid_int = (unsigned long int)tid;

  cout << "The Product is: " << val1 * val2 << endl;
  cout << "The thread id of this product thread is: " << tid_int << endl;

  return NULL;
}