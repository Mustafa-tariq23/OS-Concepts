#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
int main(){
  int n = 0;
  int id = fork();
  if(id == 0){
    n = 1;
  }
  else{
    n = 6;
  }
  if(id != 0) {
    wait(NULL);
  }

  for(int i = n; i < n+5; i++){
    std::cout << i << std::endl;
  }

  return 0;
}