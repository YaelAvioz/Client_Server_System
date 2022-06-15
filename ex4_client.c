#define TIMEOUT 'Client closed because no response was recived from the server for 30 seconds'
#define ERROR

int main(int argc, char *argv[]) {
    
	// Validates the input
    if (argc != 5) {
        return ERROR
    }
