//Yael Avioz 207237421

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define TRUE 1
#define LEN 100

int calculator(int first, int operation, int second)
{
    int resulte;

    // Addition
    if (operation == 1)
    {
        resulte = first + second;
    }

    // Subtraction
    else if (operation == 2)
    {
        resulte = first - second;
    }

    // Multiplication
    else if (operation == 3)
    {
        resulte = first * second;
    }

    // Division
    else if (operation == 4)
    {
        resulte = first / second;
    }

    // In case the operation is not valid
    else
    {
      printf("ERROR_FROM_EX4\n");
      exit(-1);
    }

    // Returns the final resulte
    return resulte;
}

// Handles the client
void server_handler(int signum)
{
    printf("work\n");

    // Create a child process
    int child_p = fork();

    // In case of failure
    if (child_p == -1)
    {
      printf("ERROR_FROM_EX4\n");
      exit(-1);
    }

    if (child_p == 0)
    {

        // Open the client file with the flag read only
        int file = open("to_srv.txt", O_RDONLY);

        // In case there was a failiure
        if (file < 0)
        {
          close(file);
          printf("ERROR_FROM_EX4\n");
          exit(-1);
        }

        // Create buffer
        char buffer[LEN];

        // Reads data from the client file to the buffer
        int read_file = read(file, buffer, LEN);

        // In case there was a failiure
        if (read_file == -1)
        {
          printf("ERROR_FROM_EX4\n");
          exit(-1);
        }

        // Removes the client file
        close(file);
        int ret = remove("to_srv.txt");

        // In case there was a failiure
        if (ret == -1)
        {
          printf("ERROR_FROM_EX4\n");
          exit(-1);
        }

        // Parse input from buffer
        // Save the data from the buffer to variables
        const char s[3] = "\n";
        char *token;
        token = strtok(buffer, s);
        int client_pid = atoi(token);
        token = strtok(NULL, s);
        int first = atoi(token);
        token = strtok(NULL, s);
        int operation = atoi(token);
        token = strtok(NULL, s);
        int second = atoi(token);
        
        // Convert the client pid to string
        char client_pid_str[LEN];
        sprintf(client_pid_str, "%d", client_pid);

        // Create the output file name
        char file_name[LEN];
        strcpy(file_name, "to_client_");
        strcat(file_name, client_pid_str);
        strcat(file_name, ".txt");
        
		// In case user is trying to divide by zero
        if((operation == 4) && (second == 0))
        {
          // Create the file
          int to_client_file = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);

          // Write the resulte to "to_client_xxxxx.txt" file
          write(to_client_file,"CANNOT_DIVIDE_BY_ZERO", strlen("CANNOT_DIVIDE_BY_ZERO"));
          write(to_client_file, "\n", strlen("\n"));
        
          // Close the file
          close(to_client_file);
        
          // Send signal to the client
          kill(client_pid, SIGUSR2);
          exit(0);
        }
        else{
          // Calc the resulte
          int answere = calculator(first, operation, second);

          // Convert the resulte to string
          char answere_str[LEN];
          sprintf(answere_str, "%d", answere);

          // Create the file
          int to_client_file = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);

          // Write the resulte to "to_client_xxxxx.txt" file
          write(to_client_file, answere_str, strlen(answere_str));
          write(to_client_file, "\n", strlen("\n"));
        
          // Close the file
          close(to_client_file);
        
          // Send signal to the client
          kill(client_pid, SIGUSR2);
          exit(0);
        }
    }
}


// TIMEOUT
void alarm_handler(int sig){
    printf("The server was closed because no service request was received for the last 60 seconds\n");
    exit(0);
}

int main()
{
    signal(SIGALRM, alarm_handler);
    signal(SIGUSR1, server_handler);

    alarm(60);
    while (TRUE)
    {
        pause();
    }

    return 0;
}