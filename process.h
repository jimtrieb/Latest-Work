//Jim Trieb
//z1912658
//csci 480 PE1
//assignment 3
//3-21-22

#ifndef PROCESS
#define PROCESS

#include <string>
#include <vector>
#include <fstream>
using namespace std;

class process //class for each process
{
	public:
		string processName; //name of process
		int processID; //will use consecutive values

		vector <pair<char, int>> history; //vector to hold type of burst and burst time
		int subscript; //subscript into vector

		int cpuTimer; //clock tick for cpu burst
		typedef int ioTimer;
		ioTimer inputTimer; //clock ticks for input burst
		ioTimer outputTimer; //clock ticks for output burst

		int cpuTotal; //number of clock ticks while active
		typedef int ioTotal;
		ioTotal inputTotal; //number of clock ticks for input active
		ioTotal outputTotal; //number of clock ticks for output active

		typedef int ioCount;
		ioCount inputCount; //number of completed input burst
		ioCount outputCount;//number of completed output burst
		int cpuCount; //number of completed cpu burst
		int arrivalTime;

		//name: burstIsOver
		//use: determine if burst is over
		//parameter: current time
		//return: true if over false if not
		bool burstIsOver(int time);

		//name:goToNextBurst
		//use: move through vector to go to next burst
		//parameter: subscript of vector that holds burst
		//returns: none
		void goToNextBurst() {subscript++;}
		
		//name: doingInput
		//use: determine if process is doing input
		//parameter: none
		//return: true if doing input
		bool doingInput() {return history[subscript].first == 'I';}

		//name: doingOutput
		//use: determine if process is doing output
		//parameter: none
		//return: true if doing output
		bool doingOutput() {return history[subscript].first == 'O';}

		//name: isTerminated
		//use: determine if process is terminated
		//parameter: none
		//return: true if process is terminated
		bool isTerminated() {return history[subscript].first == 'N' | subscript >= history.size();}

		//name:printSummary
		//use: print statistics of process
		//parameter: none
		//returns: none
		void printSummary();

		int waitingTime(); //holds time waiting for a process
		int endingTime; //ending time of process
		int startTime; //start time of process

		//name: currentBurstTime
		//use: to get the burst time of process
		//parameter: none
		//returns: the burst time of a burst
		int currentBurstTime() {return  history[subscript].second;}
};

#endif
