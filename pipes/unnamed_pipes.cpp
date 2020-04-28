#include <iostream>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char * argv)
{
    // Create a pid for the child process
    pid_t child = -1;
    // Create a pipedescriptor 
    int pipedes[2] = {-1};
    // char ch = '\0';

    int ret_val = -1;
    
    // Create a pipe
    ret_val = pipe(pipedes);
    if(ret_val == -1) {
        perror(" Unable to create pipe ");
    }

    // Create child 
    child = fork();
    cout << "[Main] pid: " << getpid() << endl;

    if(child == 0) {
        // Child process
        cout << "[Child] pid" << getpid() << endl;
        cout << "[Child] child var: " << child << endl;
        // cin >> ch;

        // Close the write end of the pipe
        close(pipedes[1]);
        // cin >> ch;

        // Read data from pipe
        char buff[256] = {'\0'};
        int bytes_read = -1;
        do {
            bytes_read = read(pipedes[0], buff, 256);
            cout << "[Child] Bytes Read: " << bytes_read << endl;
            cout << "[Child] Data Read: " << buff << endl;
        } while(bytes_read != 0);

        //close the read end of pipe
        close(pipedes[0]);
        //exit the child process
        exit(EXIT_SUCCESS);

    } else {
        // Parent process
        cout << "[Parent] pid" << getpid() << endl;
        cout << "[Parent] child var: " << child << endl;
        // cin >> ch;
        // Close the read end of the pipe
        close(pipedes[0]);
        // cin >> ch;
        
        // Write into the pipe
        char buff[] = "Hey this is test string";
        int bytes_written = -1;
        for (int i = 0; i < 5; i ++) {
            bytes_written = write(pipedes[1], buff, strlen(buff));
            cout << "[Parent] Bytes_written: " << bytes_written << endl;
            cout << "[Parent] Data_written: " << buff << endl;
        }
        // close the write end of the pipe
        close(pipedes[1]);
        // exit the parent process
        exit(EXIT_SUCCESS);
    }

}