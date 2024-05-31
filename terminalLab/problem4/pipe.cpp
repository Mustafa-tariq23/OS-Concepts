#include <iostream>
#include <cstdio>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

bool isPalindrome(const std::string &str) {
    int n = str.length();
    for (int i = 0; i < n / 2; ++i) {
        if (str[i] != str[n - i - 1]) {
            return false;
        }
    }
    return true;
}


int main()
{
  const char *message = "madam";
  char buffer[128];
	pid_t pid;
	int fd[2];
	
	if(pipe(fd) == -1)
	{
		std::perror("Failed to create Pipe!");
		return -1;
	}

	pid = fork();
	if(pid == -1)
	{
		std::perror("Failed to Fork!");
		return 1;
	}
	if(pid)
	{
		close(fd[1]); // Close the write end of the pipe
    read(fd[0], buffer, sizeof(buffer));
    close(fd[0]); // Close the read end of the pipe after reading

    std::string receivedMessage(buffer);
    receivedMessage = receivedMessage.substr(0, receivedMessage.find('\0'));

    if (isPalindrome(receivedMessage)) {
      std::cout << "\"" << receivedMessage << "\" is a palindrome" << std::endl;
    } else {
      std::cout << "\"" << receivedMessage << "\" is not a palindrome" << std::endl;
    }
    } else {
      // Parent process
      close(fd[0]); 
      write(fd[1], message, strlen(message) + 1);
      close(fd[1]);
      wait(NULL);
    }

    return 0;
}
