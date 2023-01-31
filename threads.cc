
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <mutex>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 4
#define BUFFER_SIZE 10

int cookieCount = 0; //declare and initialize variables
sem_t full; //semaphores 
sem_t empty;
pthread_mutex_t mutexLock; //mutext lock

int consumerStatus[NUM_THREADS]; //array of ints to hold thread status
int producerStatus[NUM_THREADS];

using namespace std;



//function: insert_item
//use: insert a cookie into buffer
//parameters: thread ID 
//returns: 0 on success, -1 on failure
int insert_item(int threadid)
{
	if (sem_wait(&empty)) //spin until empty buffer
	{
		perror("sem_wait: ");
		return -1;
	}

	if (pthread_mutex_lock(&mutexLock)) //aquire mutex lock
	{
		perror("pthread_mutex_lock: ");
		return -1;
	}

	cookieCount++; //producers insert cookies

	cout << "producer #" << threadid << " inserted a cookie. Total: " << cookieCount << endl << flush; //print info and flush output

	if (pthread_mutex_unlock(&mutexLock)) //release lock
	{
		perror("pthread_mutex_unlock: ");
		return -1;
	}

	if (sem_post(&full)) // new fulll buffer
	{
		perror("sem_post: ");
		return -1;
	}

	return 0;
}

//function: remove_item
//use: remove a cookie from buffer
//parameters: thread ID 
//returns: 0 on success, -1 on failure
int remove_item(int threadid)
{
	if (sem_wait(&full)) //spin until there is a full buffer
	{
		perror("sem_wait: ");
		return -1;
	}


	if (pthread_mutex_lock(&mutexLock)) //aquire lock
	{
		perror("pthread_mutex_lock: ");
		return -1;
	}

	cookieCount--; //consumers take cookies

	cout << "consumer #" << threadid << " removed a cookie. Total: " << cookieCount << endl << flush; //print info and flush output

	if (pthread_mutex_unlock(&mutexLock)) //release lock
	{
		perror("pthread_mutex_unlock: ");
		return -1;
	}

	if (sem_post(&empty)) //new empty buffer 
	{
		perror("sem_post: ");
		return -1;
	}

	return 0;


}

//function: *producer
//use: executes the role of producer threads which insert cookies into buffer
//parameter: void pointer for thread ID
//returns: nothing, will terminate calling thread
void *producer(void *param)
{
	int tid = *(reinterpret_cast<int *> (param)); //get thread ID from created thread

	producerStatus[tid] = 0; //hold status of each thread

	for (int i = 0; i <= 4; i++) //each thread inserts 5 times
	{
		if (insert_item(tid)) //insert failed
		{
			producerStatus[tid] = -1;
			pthread_exit(&producerStatus[tid]);
		}

		sleep(1);
	}

	pthread_exit(&producerStatus[tid]);
}

//function: *consumer
//use: executes the role of consumer threads which remove cookies from buffer
//parameter: void pointer for thread ID
//returns: nothing, terminated calling thread
void *consumer(void *param)
{
	int tid = *(reinterpret_cast<int *> (param)); //get thread ID from created thread

	consumerStatus[tid] = 0; //holds thread status

	for (int i = 0; i <= 4; i++) //each thread consumes 5 times
	{
		if (remove_item(tid)) //remove failed
		{
			consumerStatus[tid] = -1;
			pthread_exit(&consumerStatus[tid]);
		}

		sleep(1);
	}

	pthread_exit(&consumerStatus[tid]);
}

int main()
{
	if (sem_init(&empty, 0, BUFFER_SIZE)) //initialize semaphores
	{
		perror("sen_init empty: ");
		exit(-1);
	}

	if (sem_init(&full, 0, 0))
	{
		perror("sen_init full: ");
		exit(-1);
	}

	pthread_t consumerThreads[NUM_THREADS]; //array of 5 consumer threads
	pthread_t producerThreads[NUM_THREADS]; //array of 5 producer threads

	int producerID[NUM_THREADS]; //arrays to hold thread ID
	int consumerID[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++) //4 threads of each will be created
	{
		consumerID[i] = i; //set ID of each thread
		producerID[i] = i;

		if (pthread_create(&consumerThreads[i], NULL, consumer, &consumerID[i])) //creates consumer threads and passes in consumer function
		{
			cerr << "Unable to create consumer thread" << endl;
			exit(-1);
		}

		if (pthread_create(&producerThreads[i], NULL, producer, &producerID[i])) //creates producer threads and passes in producer function
		{
			cerr << "Unable to create producer thread" << endl;
			exit(-1);
		}
	}

	for (int i = 0; i < NUM_THREADS; i++) //join producer threads
	{
		if (pthread_join(producerThreads[i], NULL))
		{
			cerr << "Unable to join producer threads" << endl;
		}
	}

	for (int i = 0; i < NUM_THREADS; i++) //join consumer threads
	{
		if (pthread_join(consumerThreads[i], NULL))
		{
			cerr << "Unable to join consumer threads" << endl;
		}
	}

	cout << "All threads are done." << endl;

	if (pthread_mutex_destroy(&mutexLock)) //destory mutex
	{
		perror("pthread_mutex_destroy: ");
		return -1;
	}

	sem_destroy(&full); //destory semaphores
	sem_destroy(&empty);
	
	cout << "Resources cleaned up." << endl;

	for (int i = 0; i < NUM_THREADS; i++) //prints out which threads had failed
	{
		if (producerStatus[i])
		{

			cerr << "Producer thread " << i << " failed: " << producerID[i] << endl;
		}

		if (consumerStatus[i])
		{
			cerr << "Consumer thread " << i << " failed: " << consumerID[i] << endl;
		}
	}

	return 0;
}
