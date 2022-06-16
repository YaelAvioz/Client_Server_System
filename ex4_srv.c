#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>


#define TRUE 1
#define ERROR
#define LEN 100


int calculator(int first, int operation, int second)
{
	int resulte;
	
	// Addition
	if(operation == 1)
	{
		resulte = first + second;
	}
	
	// Subtraction
	else if(operation == 2)
	{
		resulte = first - second;
	}
	
	// Multiplication
	else if(operation == 3)
	{
		resulte = first * second;
	}
	
	// Division
	else if(operation == 4)
	{
		// Cannot divide by zero
		if(second == 0 )
		{
			return ERROR;
		}
		resulte = first / second;
	}
	
	// In case the operation is not valid
	else{
		return ERROR;
	}
	
	// Returns the final resulte
	return resulte;
}


// Handles the client
void handler(int signum)
{
  printf("work\n");
  
	// Create a child process
	int child_p = fork();
	
	// In case of failure
	if(child_p == -1)
	{
		return ERROR;
	}
	
	// Open the client file with the flag read only
	int file = open("to_srv.txt", O_RDONLY);
		
	// In case there was a failiure
	if(file < 0)
	{
		close(file);
		return ERROR;
	}
		
	// Create buffer
	char buffer[LEN];
		
	// Reads data from the client file to the buffer
	int read_file = read(file, buffer, LEN);
 

	// In case there was a failiure
	if (read_file == -1)
	{
		return ERROR;
	}
		
	// Removes the client file
	close(file);
	int ret = remove("to_srv.txt");

	// In case there was a failiure
	if (ret == -1)
	{
		return ERROR;
	}
 
		
	// Parse input from buffer
   printf("in buffer:\n");
   printf("%s\n\n", buffer);
   
   const char s[3] = "\n";
   char *token;
   
   /* get the first token */
   token = strtok(buffer, s);
   
   int client_pid = atoi(token);
   token = strtok(NULL, s);
   int first = atoi(token);
   token = strtok(NULL, s);
   int operation = atoi(token);
   token = strtok(NULL, s);
   int second = atoi(token);
      
   printf("client: %d\n\n", client_pid);
   printf("first: %d\n\n", first);
   printf("opration: %d\n\n", operation);
   printf("second: %d\n\n", second);
   
  //calc the resulte
  printf("START CALC..\n\n");
	int answere = calculator(first,operation,second);
 printf("calc..calc..calc...");
  printf("the answere is: %d" ,answere);
   
 }
	
	/** 
	
	// Convert answere to string
	char answere_str[10];
    sprintf(answere_str, '%d', answere);
	
	// Get Client PID
	char client_pid[10];
	//pid= //check hoe to get this data
    //sprintf(answere_str, 'to_client_%d', pid);
	
 //	write the resulte to "to_client_xxxxx.txt" file
}*/
	
	

int main (){

  printf("\nstart\n");
  
  signal(SIGUSR1,handler);
  
  while(TRUE) {
    printf("\nwaiting...\n");
    pause();
  }
    
  return 0;
}
