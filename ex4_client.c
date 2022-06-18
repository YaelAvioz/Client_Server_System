#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define LEN 100

void client_handler(int signum)
{
    // Create the output file
    char client_pid_str[LEN];
    char file_name[LEN];
    sprintf(client_pid_str, "%d", getpid());
    strcpy(file_name, "to_client_");
    strcat(file_name, client_pid_str);
    strcat(file_name, ".txt");
    
    // Open the client file with the flag read only
    int file = open(file_name, O_RDONLY);

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
    int ret = remove(file_name);

    // In case there was a failiure
    if (ret == -1)
    {
        printf("ERROR_FROM_EX4\n");
        exit(-1);
    }
    
    // Parse input from buffer
    const char s[3] = "\n";
    char *token;
    token = strtok(buffer, s);
    char *resulte = token;

    printf("%s\n", resulte);
}

int main(int argc, char *argv[])
{

    // Validates the input
    if (argc != 5)
    {
        printf("ERROR_FROM_EX4\n");
        exit(-1);
    }
    
    // Get the server pid
    int srv_pid = atoi(argv[1]);

    // Get the client pid
    char client_pid_str[LEN];
    int client_pid = getpid();
    sprintf(client_pid_str, "%d", client_pid);

    // Create the file
    int to_srv_file = open("to_srv.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

    // Write the input to txt file
    write(to_srv_file, client_pid_str, strlen(client_pid_str));
    write(to_srv_file, "\n", strlen("\n"));
    write(to_srv_file, argv[2], strlen(argv[2]));
    write(to_srv_file, "\n", strlen("\n"));
    write(to_srv_file, argv[3], strlen(argv[3]));
    write(to_srv_file, "\n", strlen("\n"));
    write(to_srv_file, argv[4], strlen(argv[4]));

    // Sends signal to server
    // SIGUSR1 - Intended for use by user applications
    kill(srv_pid, SIGUSR1);

    signal(SIGUSR2, client_handler);
    
    alarm(30);
    pause();
    
    return 0;
}
