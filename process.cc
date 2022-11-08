//Jim Trieb
//z1912658
//csci 480 PE1
//assignment 2
//2-28-22


#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
using namespace std;

/*
                    granParent
                    /          \
	intermediateParent    brother
               |
           grandChild
*/




/* table below shows each process values in forkResult and forkResult2 variables
   
process                |       forkResult     |     forkResult2     
================================================================================
grandParent pid   =    |  pid of interMed     |    pid of brother
------------------     |                      |
intermediateParentpid= |       0              |   pid of grandChild
__________________     |                      |
brother pid  =         |  pid of interMed     |        0
_________________      |                      |
grandChild pid   =     |       0              |        0
*/


int WRITE_SIDE = 1; //use for writing to pipe
int READ_SIDE = 0; //use to reading from pipe




//Function: amIGrandParent
//Use: determine if process is grand parent process
//parameters: 2 process ids from the 2 fork calls in main
//returns: true if grandparent, false otherwise
bool amIGrandParent(pid_t p1, pid_t p2)
{
	if ((p1 != 0) && (p2 != 0))
	{
		return true;
	}

	return false;

}

//Function: amIIntermediateParent
//Use: determine if process is intermediate parent process
//parameters: 2 process ids from the 2 fork calls in main
//returns: true if intermediate, false otherwise
bool amIIntermediateParent(pid_t p1, pid_t p2)
{
	if ((p1 == 0) && (p2 != 0))
	{
		return true;
	}

	return false;

}

//Function: amIBrother
//Use: determine if process is brother process
//parameters: 2 process ids from the 2 fork calls in main
//returns: true if brother, false otherwise
bool amIBrother(pid_t p1, pid_t p2)
{
	if ((p1 != 0) && (p2 == 0))
	{
		return true;
	}

	return false;	
}

//Function: amIGrandChild
//Use: determine if process is grand Child process
//parameters: 2 process ids from the 2 fork calls in main
//returns: true if grand child, false otherwise
bool amIGrandChild(pid_t p1, pid_t p2)
{
	if ((p1 == 0) && (p2 == 0))
	{
		return true;		
	}

	return false;
}



//Funtion: createPipe
//use: create a pipe
//parameters: int pointer to pipe
//retunrs: none 
void createPipe(int *p)
{
	if (pipe(p) < 0)
	{
		cerr << "Could not make pipe" << endl;
		exit(1);
	}

}



//function:: printTagMessage
//use: prints a message to cout all at once
//parameters: a tag you want to print (process name) and the message you want to print
//returns: none
void printTagMessage(string tag, string message)
{
	string print = tag + ": " + message + "\n\n";
	cout << print;

}



//function: printInfo
//use: to print info about each process 
//parameters: a tag (process name) and message you want to print
//returns: none
void printInfo(string tag, string message)
{
	printTagMessage(tag,"My PID is " + to_string(getpid()) + ", my parents's PID is " + to_string(getppid()) + ". " + message);
}


//function: printAwake
//use: print I am awake message for process
//parameters: tag to print (process name)
//returns: none
void printAwake(string tag)
{
	string print = tag + " " + to_string(getpid()) + ": I am awake.\n";
	cout << print;

}


//function: readFromPipe
//use: read message from a pipe
//parameters: pipe to read from, and the message length
//returns: message read in a string
string readFromPipe(int p, int length)
{
	char message[64]; //buffer for message
	bool done = false; //have not read yet
	while (!done) //while still more to read
	{
		int nread = read(p, message, length);

		switch (nread)
		{
			case -1:
				if (errno == EAGAIN)
				{
					sleep(1); //sleep then try again 
					break;
				}

				else
				{
					cerr << "Read failed " << errno <<endl;
					
					exit(1);

				}
				break;
			default:
				done = true; //finished reading message	
				break;
		
		}
	}

	string s(message); //put message in string to return

	return s;
	
}


//function: writeToPipe
//use: write to a pipe
//parameters: pipe to use, the message , and the length of message
//returns: none
void writeToPipe(int p, const char *message, int length)
{
	int bytesWritten = 0; //have not written anything yet
	
	while (1) //keep writing until all of message written
	{
		int writeReturn = write(p, message+bytesWritten, length-bytesWritten); //check for partial writes

		if (writeReturn == -1) 
		{
			cerr << "Write failed" << endl;
			exit(1);
		}

		bytesWritten += writeReturn;

		if (bytesWritten >= length) //done writing when bytes written to pipe exceeds message length
		{
			break;
		}
	}
}

//function: showAllProcesses
//use: execute comamnd to show all processes
//parameters: 2 process id's of both fork results, can use those 2 process ids to find children
//returns: none
void showAllProcesses(int pid, int pid2)
{
	string command = "/bin/ps -f --ppid " + to_string(pid) + "," + to_string(pid2) + "," + to_string(getpid()) + "," + to_string(getppid()); //put comamnd together
	printTagMessage("Grand Parent","Issuing command: " + command); 
	system(command.c_str()); //call to system to execute command

}




//note: the if loops for each process are almost identicall if they are both reading or both writing

int main()
{

	setbuf(stdout, NULL);
	
	int pipe_a[2], pipe_b[2]; //declare pipes 

	createPipe(pipe_a); //create pipes to communicate between processes
	createPipe(pipe_b);


	pid_t grandParent = getpid(); //record grand parent pid before creating child processes
	pid_t forkResult = fork();
	pid_t forkResult2 = fork();
	

	if (amIGrandParent(forkResult, forkResult2)) //inside if is grand parent process
	{      
		string message = "Go do some chores."; 

		writeToPipe(pipe_a[WRITE_SIDE], message.c_str(), message.length() + 1); //write message to pipe

		printInfo("Grand Parent", "My Children are " + to_string(forkResult) + ", " + to_string(forkResult2) + ". I wrote to pipe A: " + message);

		showAllProcesses(forkResult, forkResult2); //pid of intermediate parent and brothe to catch children if any

		while (wait(NULL) > 0); //wait for child process to finish

		cout << "Grand Parent: Child processes finished their work." << endl;


	}

	if (amIBrother(forkResult, forkResult2)) //inside if is brother process
	{
		string message = readFromPipe(pipe_a[READ_SIDE], 19); //read from grandparent

		string readFrom = "I read from pipe A: ";

		readFrom.append(message); //put message together

		printInfo("Brother", readFrom);

		sleep(3); //process will sleep for 3 seconds

		printAwake("Brother");

		
	}

	if (amIIntermediateParent(forkResult, forkResult2)) //inside if is intermediate parent process
	{
		string message = "Go do some chores.";

		writeToPipe(pipe_b[WRITE_SIDE], message.c_str(), message.length() + 1); //write to pipe b messagei
		
		printInfo("Intermediate Parent", "I wrote to pipe B: " + message);

		sleep(3);

		printAwake("Intermediate Parent");
	}

	if (amIGrandChild(forkResult, forkResult2))
	{
		string message = readFromPipe(pipe_b[READ_SIDE], 19); //read message from intermediate parent

		string readFrom = "I read from pipe B: ";

		readFrom.append(message); //create message to print

		printInfo("Grandchild", readFrom);

		sleep(3);

		printAwake("Child");
		

	}


	close(pipe_a[WRITE_SIDE]); //close pipes
	close(pipe_b[WRITE_SIDE]);
	close(pipe_a[READ_SIDE]);
	close(pipe_b[READ_SIDE]);

	return 0;
}
