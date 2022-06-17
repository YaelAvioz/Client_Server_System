#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define ERROR -1

int main(int argc, char *argv[])
{

    // Validates the input
    if (argc != 5)
    {
        return ERROR;
    }

    // Get the server pid
    int srv_pid = atoi(argv[1]);

    // Create the file
    int to_srv_file = open("to_srv.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

    // Write the input to txt file
    write(to_srv_file, "12345", strlen("12345"));
    write(to_srv_file, "\n", strlen("\n"));
    write(to_srv_file, argv[2], strlen(argv[2]));
    write(to_srv_file, "\n", strlen("\n"));
    write(to_srv_file, argv[3], strlen(argv[3]));
    write(to_srv_file, "\n", strlen("\n"));
    write(to_srv_file, argv[4], strlen(argv[4]));

    // Sends signal to server
    // SIGUSR1 - Intended for use by user applications
    kill(srv_pid, SIGUSR1);

    return 0;
}
