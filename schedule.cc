
#include "scheduler.h"
#include "process.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

deque <process*> scheduler::entry; //create deques
deque <process*> scheduler::ready;
deque <process*> scheduler::output;
deque <process*> scheduler::input;
deque <process*> scheduler::terminated;

int scheduler::pid = 100; //declare and initialize values
int scheduler::time = 0;
process* scheduler::active = 0;
process* scheduler::iActive = 0;
process* scheduler::oActive = 0;
bool scheduler::idle = false;
int scheduler::totalTimeIdle = 0;


void scheduler::init(string fileName)
{
	ifstream file (fileName);
	if (file.is_open()) //file open
	{
		while (!file.eof()) 
		{


			process* newProcess = readProcess(file); //store new process
			if (newProcess == 0)
			{
				break;
			}
			
			if (newProcess->history[0].first != 'N') //push process onto entry if it has burst to do 
			{
				entry.push_back(newProcess); 
			}


		}

		file.close();
	}

	else
	{
		cerr << "File could not be opened" << endl;
		exit(1);
	}


	populateReadyQ(); 
	
}



process* scheduler::readProcess(ifstream &file)
{
	string processName;  
	file >> processName;

	if (processName.length() == 0)
	{
		return 0;
	}

	
	process *createdProcess = new process; //create process

	createdProcess->subscript = 0; //initialize process values
	createdProcess->cpuTimer = 0;
	createdProcess->inputTimer = 0;
	createdProcess->outputTimer = 0;
	createdProcess->processID = ++pid;
	createdProcess->cpuTotal = 0;
	createdProcess->outputTotal = 0;
	createdProcess->inputTotal = 0;
	createdProcess->cpuCount = 0;
	createdProcess->inputCount = 0;
	createdProcess->outputCount = 0;	
	createdProcess->processName = processName; 
       	file >> createdProcess->arrivalTime;



	for (int i = 0; i < 10; i++) //for each pair of values in input file
	{
		char burst;
		int duration;
		file >> burst;
		file >> duration;
		createdProcess->history.push_back(make_pair(burst, duration)); //push process onto vector with its burst types and times
	}
	
	return createdProcess; //return the new process
}



void scheduler::outputProcessPid(string tag, process* p)
{
	cout << tag << " is ";

	if (p) //if there is a process
	{
		cout << p->processID;
	}

	else
	{
		cout << 0;
	}

	cout << endl;
}


void scheduler::outputDequeContent(string tag, const deque<process*>& d)
{
	cout << "Contents of the " << tag << " Queue:" << endl;
	
	if (d.size() == 0)
	{
		cout << "(empty)" << endl;
	}

	else //if deque is not empty
	{
		for (int i = 0; i < d.size(); i++)
		{
			cout << (d[i])->processID << "    ";

		}

		cout << endl;

	}

}


void scheduler::showState()
{
	outputProcessPid("Active", active); 	
	outputProcessPid("IActive", iActive); 	
	outputProcessPid("OActive", oActive);
	outputDequeContent("Entry", entry);	
	outputDequeContent("Ready", ready);	
	outputDequeContent("Input", input);	
	outputDequeContent("Output", output);		
}

bool scheduler::moveNextAvailableEntryToReady()
{


	process* p = entry[0]; //get first process from entry

	if (time >= p->arrivalTime)
	{
		cout << "Process " << p->processID << " moved from Entry Queue into the Ready Queue at time " << currentTime() << endl << endl;
		entry.pop_front(); //delete process from entry

		p->startTime = currentTime();

		ready.push_back(p); //move process to ready
		return false;
	}

	return true;	

}

void scheduler::moveActiveToTerminated()
{
	cout << "Process " << active->processID << " has ended." << endl;
	terminated.push_back(active); //move process to terminated
	active->endingTime = currentTime(); //set ending time of process
	active->printSummary();
	active = 0; //no active process

}

void scheduler::moveNextReadyToActive()
{
	
	process* p = ready[0]; //get process from ready
	ready.pop_front(); //delete process


	if (p->isTerminated())
	{
		terminated.push_back(p);
	}

	else
	{
		active = p; 
		active->cpuCount++;
	}
}


void scheduler::moveActiveToOutput()
{
	active->cpuTimer = 0;
	output.push_back(active);
	active = 0;
}

void scheduler::moveOutputToOactive()
{
	process* p = output[0];
	output.pop_front();
	oActive = p;
	oActive->outputCount++;
}
void scheduler::moveInputToIactive()
{
	process* p = input[0];
	input.pop_front();
	iActive = p;
	iActive->inputCount++;
}

void scheduler::moveIactiveToReady()
{
	iActive->inputTimer = 0;
	ready.push_back(iActive);
	iActive = 0;
}

void scheduler::moveOactiveToReady()
{
	oActive->outputTimer = 0;
	ready.push_back(oActive);
	oActive= 0;
}

void scheduler::moveActiveToInput()
{
	active->cpuTimer = 0;
	input.push_back(active);
	active= 0;
}

bool scheduler::isReadyToAddProcess() //determine if process can go from entry to ready queue
{
	int currentlyInUse = 0;

	if (active) currentlyInUse++;
	if (iActive) currentlyInUse++;
	if (oActive) currentlyInUse++;

	currentlyInUse += ready.size();
	currentlyInUse += input.size();
	currentlyInUse += output.size();

	return (currentlyInUse <= IN_USE); //true if ready to add process

}

bool scheduler::noProcesses()
{
	if (entry.empty() && input.empty() && output.empty() && ready.empty() && active == 0 && iActive == 0 && oActive == 0) //all queues and pointers empty
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool scheduler::completed()
{

	if (active && active->isTerminated())
	{
		moveActiveToTerminated();
	}

	if (noProcesses()) //completed if no processes
	{
		return true;
	}

	if (time == MAX_TIME) //completed if at max time
	{
		return true;
	}

	return false;
}

bool scheduler::isActiveProcess() //determines if active process
{
	return active;
}

void scheduler::run()
{
	updateActive();
	updateInput();
	updateOutput();

	handleActive();
	handleInput();
	handleOutput();
}

void scheduler::updateActive()
{
	if (!active) 
	{
		if (!ready.size()) 
		{
			populateReadyQ();
		}

		if (ready.size()) //move process to active if there is one available and active is empty
		{	
			moveNextReadyToActive();
		}
	}
}

void scheduler::updateInput()
{
	if (!iActive) 
	{
		if (input.size())
		{
			moveInputToIactive(); //move process to Iactive if iactive is empty and there is a process in input queue
		}
	}
}

void scheduler::updateOutput()
{
	if (!oActive) 
	{
		if (output.size())
		{
			moveOutputToOactive(); //move process to oActive if oactive is empty and there is a process in output queue
		}
	}
}

void scheduler::handleInput()
{
	if (iActive)
	{
		iActive->inputTimer++; //update stats
		iActive->inputTotal++;
		if (iActive->burstIsOver(time)) //if iactive burst over move to ready queue
		{
			iActive->goToNextBurst(); //go to next burst
			moveIactiveToReady();
		}
	}

	else
	{
		if (input.size()) //if something in input queue
		{
			moveInputToIactive();
		}
	}

}


void scheduler::handleOutput()
{
	if (oActive) //if there is an oactive process
	{
		oActive->outputTimer++; //update stats
		oActive->outputTotal++;
		if (oActive->burstIsOver(time)) //if burst is over move to ready queue
		{
			oActive->goToNextBurst(); //go to next burst
			moveOactiveToReady();
		}
	}

	else
	{
		if (output.size()) //if something in output queue
		{
			moveOutputToOactive();
		}
	}
}

void scheduler::handleActive()
{
	if (isActiveProcess()) 
	{
		runActiveProcess(); //run an active process if there is one
		idle = false;
	}

	else
	{
		if (!idle)
		{
			idle = true;
			cout << "At time " << time << " Active is 0, so we have idle time for a while" << endl << endl; //idle
		}

		totalTimeIdle++;
	}
}

void scheduler::tick()
{
	time++;
}

void scheduler::runActiveProcess()
{
	active->cpuTimer++; //update stats
	active->cpuTotal++;
	if (active->burstIsOver(time)) //if burst is over
	{
		active->goToNextBurst(); //go to next burst

		if (active->doingInput()) //ask if process is doing input burst
		{
			moveActiveToInput();
		}


		else if (active->doingOutput()) //ask if process is doing output burst
		{
			moveActiveToOutput();
		}

	}
}

void scheduler::showFinalState()
{
	cout << "The run has ended." << endl;
	cout << "The final value of the timer was:  " << time << endl;
	cout << "The amount of time spent idle was:  " << totalTimeIdle  << endl;
	cout << "Number of terminated processes = " << terminated.size() << endl;
	cout << "Average waiting time for all terminated processes = " << averageWaitingTime() << endl;
	showState();	
}
			

void scheduler::populateReadyQ()
{
	bool done = false;

	while (isReadyToAddProcess() && entry.size() && !done)
	{				
		done = moveNextAvailableEntryToReady();
	}
}

int scheduler::averageWaitingTime()
{
	int totalWaitTime = 0;

	for (int i = 0; i < terminated.size(); i++) //get waiting time of each terminated process
	{
		totalWaitTime += terminated[i]->waitingTime();	
	}	

	if (terminated.size() == 0)
	{
		return 0;
	}

	return totalWaitTime / terminated.size(); //avg waiting time

}
