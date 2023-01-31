
#include <iostream>
#include <vector>
#include <cstdint>
#include <mutex>
#include <thread>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>
#include <string>


using namespace std;

constexpr int rows = 1000; /// < the number of rows in the work matrix
constexpr int cols = 100; /// < the number of cols in the work matrix

std::mutex stdout_lock ; /// < for serializing access to stdout

std::mutex counter_lock; /// < for dynamic balancing only
volatile int counter = rows; /// < for dynamic balancing only

std::vector<int> tcount; /// < count of rows summed for each thread
std::vector<uint64_t> sum; /// < the calculated sum from each thread

int work[rows][cols]; /// < the matrix to be summed



/**
 * sums the rows of matrix using static load balancing
 *
 * @param tid the thread ID of each thread, assigns each thread a #
 * @param num_threads the number of threads used
 *
 * @note default is 2 threads and static
 ***********************************************************************/
void sum_static(int tid, int num_threads);


/**
 * sums the rows of matrix using dynamic load balancing
 *
 * @param tid the thread ID of each thread, assigns each thread a #
 **********************************************************************/
void sum_dynamic(int tid);

/**
 * usage statment explaing to user how to use command line arguments
 **********************************************************************/
static void usage()
{
	cerr << "Usage : reduce [-d] [-t number of threads to use]" << endl;
	cerr << "-d use dynamic load balancing (static is default)" << endl;
	cerr << "-t specify number of threads to use (default is 2 threads)" << endl;

	exit(1);
}


/**
 * prints the output string for the amount of work done by each thread
 *
 * @param s the string that will be printed to std out
 *
 * @note locks before print and unlcoks after print
 **********************************************************************/
void print(string s);

/**
 * initialize the matrix with a set of random numbers
 **********************************************************************/
void initialize();


/**
 * sums 1 row of matrix
 *
 * @param rowNum the row number to be summed
 *
 * @return the total sum for that row
 **********************************************************************/
uint64_t sumRow(int rowNum);

/**
 * gets all the rows summed in the matrix
 *
 * @return number of rows summed
 **********************************************************************/
int sumAllRows();

/**
 * gets the gross sum by adding sum of each thread
 *
 * @return the gross sum of all work done by each thread added up
 **********************************************************************/
uint64_t getGrossSum();

/**
 * grabs the next row to be summed
 *
 * @return the number of the next row
 *
 * @note used only in dynamic load balancing
 **********************************************************************/
int grabNextRow();

/**
 * main function calls functions to create and sum each row of an array with threads
 *
 * @param argc # of command line arguments
 * @param argv array of character pointers
 *
 * @return 0 on successful run
 ************************************************************************************/
int main(int argc, char **argv)
{
	bool dynamicFlag = false; //static used on default
	int opt;
	unsigned int num_threads = 2; //default is 2 threads

	unsigned int maxSupport = std::thread::hardware_concurrency(); //determine number of cores in system


	while ((opt = getopt (argc, argv, "dt:")) != -1)
	{
		switch (opt)
		{
			case 'd':
			{
				dynamicFlag = true; //use dynamic load balancing
				break;
			}
			case 't':
			{
				std::istringstream iss (optarg);
				iss >> num_threads; //get number of threads from command line
				if (maxSupport < num_threads)
				{
					num_threads = maxSupport; //if user wants to use more threads than cores the program with be run with max threads it can support
				}

			        break;
			}
			default: 
			{
			       usage (); //print out usage statement
			       break;
			}
		}
	}

	if (optind < argc)
	{
		usage(); //print out usage for incorrect command line arguments
	}
	
	sum.assign(num_threads, 0); //each thread has a sum total of 0 initially

	tcount.assign(num_threads, 0); //each thread has summed 0 rows initially

	string s = to_string(maxSupport) + " concurrent threads supported."; //prints out message with the max threads supported by hardware
	cout << s << endl;

	initialize(); //initialize array 

	std::vector<std::thread> myThreads; //create a vector of threads used for joining

	if (dynamicFlag)
	{

		for (unsigned int i = 0; i < num_threads; i++)
		{
			myThreads.push_back(std::thread(sum_dynamic, i)); //sum each thread dynamically and put into myThreads vector
		}
	}

	else
	{
		for (unsigned int i = 0; i < num_threads; i++)
		{
			myThreads.push_back(std::thread(sum_static, i, num_threads)); //sum each thread statically and put into myThreads vector
		
		}
	}

	for (unsigned int a = 0; a < myThreads.size(); a++)
	{
		if (myThreads[a].joinable())
		{
			myThreads[a].join(); //join together threads
		}		
	}

	cout << "main() exiting, total_work=" <<  sumAllRows() << " gross_sum=" << getGrossSum() << endl; //print amount of rows summed and the total gross sum 

	return 0;
}

void sum_static(int tid, int num_threads)
{
	string s = "Thread " + to_string(tid) + " starting"; //print message for when each thread starts
	
	print(s);

	for (int i = tid; i < rows; i += num_threads) //iterate through array by number of threads used
	{
		sum[tid] += sumRow(i); //running total of the sum for each thread  
		tcount[tid]++; //running total of rows summed for each thread
	}			
	
	string t = "Thread " + to_string(tid) + " ending tcount=" + to_string(tcount[tid]) + " sum=" + to_string(sum[tid]); //prints # of rows summed by each thread and total sum 
	print(t);

}

void sum_dynamic(int tid)
{
	string s = "Thread " + to_string(tid) + " starting"; //print message for when each thread starts
	
	print(s);

	int i = grabNextRow(); //grabs the next row to be summed

	while (i >= 0) //while still more rows to grab
	{
		sum[tid] += sumRow(i); //running total of the sum for each thread
		tcount[tid]++; //running total of rows summed for each thread
		i = grabNextRow(); //grabs next row to be summed
	}

	string t = "Thread " + to_string(tid) + " ending tcount=" + to_string(tcount[tid]) + " sum=" + to_string(sum[tid]); //prints # of rows summed by each thread and total sum
	print(t);

}

void initialize()
{
	srand(0x1234); //random number generator

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			work[i][j] = rand(); //fill matrix with values	
		}
	}
}

uint64_t sumRow(int rowNum)
{
	uint64_t sumOfRow = 0; //initial sum

	for (int i = 0; i < cols; i++)
	{
		sumOfRow += work[rowNum][i]; //sums each collum in a row 
	}

	return sumOfRow; //return sum of row
}


void print(string s)
{
	stdout_lock.lock(); //lock std out for printing

	cout << s << endl; //print a string

	stdout_lock.unlock(); //unlock std out
}


int sumAllRows()
{
	int total = 0; //initial number of rows summed

	for (long unsigned int i = 0; i < tcount.size(); i++)
	{
		total += tcount[i]; //get total number of rows summed
	}

	return total; //return total number of rows summed
}

uint64_t getGrossSum()
{
	uint64_t grossSum = 0; //initial gross sum

	for (long unsigned int i = 0;  i < sum.size(); i++)
	{
		grossSum += sum[i]; //adds up the sum of each thread
	}

	return grossSum; //returns total sum of each thread added together
}


int grabNextRow()
{
	counter_lock.lock(); //lock counter 
	
	int row = --counter; //decrement counter which was set to rows initially, row will be next row to be summed

	counter_lock.unlock(); //unlcok counter

	return row; //return next row to be summed
}
