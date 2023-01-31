
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include "scheduler.h"
#include "process.h"


using namespace std;

int main(int argc, char **argv)
{


	if (argc != 2) //usage message if file not specified on command line
	{
		cerr << "Usage: " << argv[0] << " filename" << endl;
		exit(1);
	}

	scheduler::init(argv[1]); //initialize values with file passed in

	while (1) //run until scheduler completes
	{

		if ((scheduler::currentTime() % scheduler::HOW_OFTEN) == 0) //print state at 25 tick intervals
		{
			cout << "Status at time " << scheduler::currentTime() << endl;
			scheduler::showState();
			cout << endl;
		}

		scheduler::run();

		scheduler::tick();


		if (scheduler::completed())
		{
			scheduler::showFinalState(); //print final stats and terminate
			break;
		}

	}

	return 0;
}

