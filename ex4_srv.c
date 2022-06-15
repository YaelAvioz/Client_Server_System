#define TRUE 1
#define ERROR
#define LEN 100


int calculator(int operation, int first, int second)
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
void handler()
{
	// Create a child process
	int child_p = fork()
	
	// In case of failure
	if(child_p == -1)
	{
		return ERROR;
	}
	
	// Open the client file with the flag read only
	int file = open('to_srv.txt', O_RDONLY);
		
	// In case there was a failiure
	if(file < 0)
	{
		close(file);
		return ERROR;
	}
		
	// Create buffer
	char buffer[LEN];
		
	// Reads data from the client file to the buffer
	int read_file1 = read(file, buffer, LEN);

	// In case there was a failiure
	if (read_file == -1)
	{
		return ERROR;
	}
		
	// Removes the client file
	close(file);
	ret = remove('to_srv.txt');

	// In case there was a failiure
	if (ret == -1)
	{
		return ERROR;
	}
		
	// Parse input from buffer
	
	// calc the resulte
	int answere = calculator();
	
	// Convert answere to string
	char answere_str[10];
    sprintf(answere_str, '%d', answere);
	
	// Get Client PID
	char client_pid[10];
	pid= //check hoe to get this data
    sprintf(answere_str, 'to_client_%d', pid);
	
	// write the resulte to "to_client_xxxxx.txt" file
}
	
	

int main (){
	
   while(TRUE) {
        pause();
    }
}
