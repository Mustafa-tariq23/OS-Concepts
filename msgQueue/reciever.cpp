#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

#define maxSize 100

struct message {
  long type;
  char text[maxSize];
};

int main() {
  // Create the message queue
  int msqid;
  key_t key;

  key = ftok("shmfile", 100);

  msqid = msgget(key, 0666 | IPC_CREAT);
  if (msqid == -1) {
    perror("msgget");
    return 1;
  }

  message msg;


  // Send the message
  if (msgrcv(msqid, &msg, sizeof(msg.text), 1, 0) == -1) {
    perror("msgsnd");
  } else {
    std::cout << "Message received: " << msg.text << "\n";
  }

  return 0;
}
