#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

#define maxSize 50

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
  msg.type = 1;

  // Prepare the message text
  std::cout << "Enter your message: ";
  std::cin.getline(msg.text, 100);

  // Send the message
  if (msgsnd(msqid, &msg, sizeof(msg.text), 0) == -1) {
    perror("msgsnd");
  } else {
    std::cout << "Message sent successfully.\n";
  }

  return 0;
}
