
#ifndef SCHEDULER
#define SCHEDULER

#include "process.h"
#include <deque>
#include <string>
using namespace std;


class scheduler
{
	private:
		static deque <process*> entry; //deques that hold process pointers for entry, ready, input, output, and terminated
		static deque <process*> ready;
		static deque <process*> output;
		static deque <process*> input;
		static deque <process*> terminated;

		static process *active; //pointer to processes, that point to active process on cpu, input, and output
		static process *iActive;
		static process *oActive;

		static bool idle; //holds idle status
		static int totalTimeIdle; //total idle time

		static const int MAX_TIME = 500; //length of whole run
		static const int IN_USE = 5; //max # of processes that can be in play at once

		//name:readProcess
		//use: read in processes from input file
		//parameter: an input specified on command line
		//return: process pointer
		static process* readProcess(ifstream &file);

		static int pid; //process ID
		static int time; //what time it is

		//name: outputProcessPid
		//use: outputs the id of each process
		//parameter: tag to print, and a process pointer
		//return: none
		static void outputProcessPid(string tag, process* p);

		//name:outputDequeContent
		//use: output content of a deque
		//parameter: tag to print and a the deque
		//return: none
		static void outputDequeContent(string tag, const deque<process*>& d);
		
		//name:noProcesses
		//use:determine if no processes are left
		//parameter: none
		//return: true if no processes left
		static bool noProcesses();

	public:
		static const int HOW_OFTEN = 25; //reprint state of system

		//name:init
		//use: create process from file and puts on entry queue
		//parameter: filename
		//return: none
		static void init(string fileName);

		//name:tick
		//use:increment the timer
		//parameter:none
		//return:none
		static void tick();

		//name:currentTime
		//use: get current time
		//parameter: none
		//return: current time
		static int currentTime() {return time;}

		//name: showState
		//use: prints state of scheduler
		//parameter: none
		//return: none
		static void showState();

		//name: isReadyToAddProcess
		//use:determine if process can go from entry to ready queue
		//parameter:none
		//return: true if ready to add process
		static bool isReadyToAddProcess();

		//name: moveNextAvailableEntryToReady
		//use: move process from entry to ready queue
		//parameter: none
		//return: false after moving
		static bool moveNextAvailableEntryToReady();

		//name: moveNextReadyToActive
		//use:move process from ready to active 
		//parameter: none
		//return: none
		static void moveNextReadyToActive();

		//name: moveActiveToInput
		//use: move process from active burst to input burst
		//parameter: none
		//return: none
		static void moveActiveToInput();

		//name: moveActiveToOutput
		//use: move process from active burst to output burst
		//parameter: none
		//return: none
		static void moveActiveToOutput();

		//name: moveOactiveToReay
		//use: move output process to ready queue
		//parameter: none
		//return:none
		static void moveOactiveToReady();

		//name: moveIactiveToReady
		//use: move inout process to ready queue
		//parameter: none
		//return: none
		static void moveIactiveToReady();

		//name: moveInputToIactive
		//use: move process from input queue to Input active
		//parameter: none
		//return: none
		static void moveInputToIactive();

		//name: moveOutputToOactive
		//use: move process from output queue to output active
		//parameter: none
		//return: none
		static void moveOutputToOactive();

		//name: moveActiveToTerminated
		//use: move active process to terminated
		//parameter: none
		//return: none
		static void moveActiveToTerminated();

		//name: completed
		//use: determine if scheduler is done
		//parameter: none
		//return: true if completed
		static bool completed();

		//name: isActiveProcess
		//use: determines if there is an active process
		//parameter: none
		//return: true if there is an active process
		static bool isActiveProcess();

		//name: run
		//use: runs the scheduler, calls handle active, input and output
		//parameter: none
		//return: none
		static void run();

		//name: handleActive
		//use: runs an active process if there is one or will idle
		//parameter: none
		//return: none
		static void handleActive();

		//name:  handleOutput
		//use: updates oActive process stats and moves when burst is over
		//parameter: none
		//return: none
		static void handleOutput();

		//name: handleInput
		//use: updates iActive process stats and moves when burst is over
		//parameter: none
		//return: none
		static void handleInput();

		//name: runActiveProcess
		//use: updates active process stats and then moves to next correct location
		//parameter: none
		//return: none
		static void runActiveProcess();

		//name: showFinalState
		//use: print finals stats 
		//parameter: none
		//return: none
		static void showFinalState();

		//name: populateReadyQ
		//use: move processes to ready queue
		//parameter: none
		//return: none
		static void populateReadyQ();

		//name: updateActive
		//use: to populate ready queue and move a process to active
		//parameter: none
		//return: none
		static void updateActive();

		//name: updateInput
		//use: decided if need to move proces to iActive
		//parameter: none
		//return: none
		static void updateInput();

		//name: updateOutput
		//use: decided if need to move process to oActive
		//parameter: none
		//return: none
		static void updateOutput();

		//name: averageWaitingTime
		//use: determine the average waiting time for processes
		//parameter: none
		//return: the average waiitng time
		static int averageWaitingTime();
};
#endif
