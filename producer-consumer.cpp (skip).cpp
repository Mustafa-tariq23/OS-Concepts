#include <iostream>
using namespace std;
#define totalNumberOfValues 10
int currentNumberOfValues = 0;


void consumer();
void producer();

// main body

int main(){

  string message;
  while(true){
    cout<<" What do you want to execute?\n Write consume to run the consumer or write produce to run the producer or write exit to complete the execution..."<<endl;
    cin>> message;

    if(message == "produce" || message == "Produce")
    {
      producer();
    }
    else if(message == "consume" || message == "Consume"){
      consumer();
    }
    else if(message == "exit" || message == "Exit"){
      break;
    }
    else{
      cout<<"Try again..."<<endl;
      cout<<" What do you want to execute?\n Write consume to run the consumer or write produce to run the producer or write exit to complete the execution..."<<endl;
      cin>> message;
    }
  }
}

// producer

void producer(){
  // while(currentNumberOfValues < totalNumberOfValues){
    currentNumberOfValues++;
    if(currentNumberOfValues > 0 && currentNumberOfValues < totalNumberOfValues){
      cout << endl << currentNumberOfValues << " Item produced"<< endl << endl;
    }
    else if(currentNumberOfValues == totalNumberOfValues){
      cout << endl << "Maximum number of items produced..."<< endl << endl;
    }
  } 
// }


void consumer () {

  if(currentNumberOfValues == 0){
    cout<< endl << "No items to consume..."<< endl << endl;
    return;
  }
  // while(currentNumberOfValues > 0){
    cout<< endl << "Consumer has consumed item number: "<< currentNumberOfValues <<endl << endl;
    currentNumberOfValues--;
  // }
}