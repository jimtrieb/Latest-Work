
#include "scheduler.h"
#include "process.h"
#include <deque>
#include <iostream>

using namespace std;

bool process::burstIsOver(int time)
{
	switch (history[subscript].first) //switch on type of burst
	{
		case 'C': 
			{	//cpu burst
			bool over = (cpuTimer >= history[subscript].second); //if timer greater than time of burst return true
			return over;
			}
			
		case 'I':
			{	//input burst 
			bool over = (inputTimer >= history[subscript].second);
			return over;
			}
			
		case 'O': 
			{	//output burst
			bool over = (outputTimer >= history[subscript].second);
			return over;
			}
		default:
			return true;
	}


}

void process::printSummary()
{
	cout << "Name:  " << processName << endl;
	cout << "Started at time " << startTime << " and ended at time " << endingTime << endl;
	cout << "Total CPU time = " << cpuTotal << " in " << cpuCount << " CPU bursts" << endl;
	cout << "Total Input time = " << inputTotal<< " in " << inputCount<< " Input bursts" << endl;
	cout << "Total Ouput time = " << outputTotal << " in " << outputCount << " Output bursts" << endl;
	cout << "Time spent in waiting: " << waitingTime() << endl;
	cout << endl << endl;

}

int process::waitingTime()
{
	return endingTime - startTime - inputTotal - outputTotal - cpuTotal; //get waiting time of process
}
