
#include<iostream>
#include<stack>
#include<deque>
#include<iomanip>
#include<string>
#include<sstream>
#include<iterator>
using namespace std;
typedef struct
{
	int id;
	string lp;
	int no_mv = 0;
}CAR; // creates struct car

//function prototypes
void get_input_vals(const string &line, char &act, string &lp);
void arrival(const CAR &car, deque<CAR> &D);
void departure(const string &lp, deque<CAR> &D, stack <CAR> &S);


int main()
{


	deque<CAR> D; //creates deque D
        stack<CAR> S; //creates stack S

	string line; // line we will be reading in from input stream
	char act; //action of car
	string lp;// string of the cars license plate
	int id = 1; //id counter for each car	

	getline(cin, line);
	while(!cin.eof())//while loop to read in lines from input file
	{

		get_input_vals(line,act,lp);//calls get inout val function
		//cout << line << endl << act << "  " << lp << endl;
		switch(act){ //switch statement based on the action the car is doing
			case 'A': //if car is arriving we choose case a
			{
				//cout << " arrival" << endl;
				CAR car;
				car.id = id;
				id++;
				car.lp = lp;
				car.no_mv = 0;

				arrival(car, D);
				cout << endl;
			}
			break;
			case 'D': //if car is leaving we choose case d
			{
				departure(lp, D, S);
			}
			break;	
			default: //default case when input stream does not contain A or D
			cout << endl <<"'" << act << "': invalid action!" << endl;
			break;

		}
		getline(cin, line);
	}

	return 0;
}
//Name: get_input_vals
//use: reads in data from input stream, and records liscense plate and action
//parameters:line is the line we are reading from input gives us data, act is the action associated with the car, and lp is the cars license plate use to identify the car
//return value: none
void get_input_vals(const string &line, char &act, string &lp)
{
	string var; //creates string var
	stringstream str_strm(line); //creates a string stream and passes in parameter line
	getline(str_strm, var, ':'); // reads from input stream with deliminating character records var
	getline(str_strm, lp, ':'); // reads from input stream with deliminating chartacter records license plate
	
	act=var[0];

}
//Name: arrival
//use: prints out when a car has arrived if deque is not full, else prints out garage is full
//parameters: the object car carries all the information on each car in garage, deque d keeps track of how many cars in garage and where they are located within
//retrun value: none
void arrival(const CAR &car, deque<CAR> &D)
{
	cout <<"Car " << car.id << " with license plate \"" <<  car.lp << "\" has arrived." << endl; //prints to std out when a car has arrived

	if(D.size() == 10) //if else statmensts pushing car in deque if it is not full (>10) and prints garage is full if it =10
	{
		cout << "The garage is full" << endl;
	}
	else
	{
		D.push_front(car);
	}


}
//name:departure
//use: will find car within deque when it is leavingm prints to std out when a car is leaving
//parameters: lp gives us the cars license plate to scan in deque for it, D is the deque we pass in basically the garage, S is the stack we use to keep the order of the cars when they are removed from the deque and put back
//return value: none
void departure(const string &lp, deque<CAR> &D, stack <CAR> &S)
{
	bool found = false; //creates boolean variable found and initializes it to false

	for (deque<CAR>::reverse_iterator itr = D.rbegin(); itr != D.rend(); itr++) //declare reverse iterator itr over the deque to scan for individual cars
	{
		CAR* pcar; //creates pointer pcar
		pcar = &*itr;//pcar is = to value of iterators position
		//cout << pcar->lp << " " << endl;

		if(lp == (*pcar).lp) // if statement matching pcar to the license plate of car in deque, used to find the car that is leaving
		{
			found = true; // if found, found now = true
			cout <<"Car " << pcar->id << " with license plate \"" <<  pcar->lp << "\" has departed," << endl;
			pcar->no_mv++;// keeps track of cars number of moves within the garage
			if(pcar->no_mv == 1)// if else statements printing out how many times the car moved within garage
			{
				cout << "    car was moved " << pcar->no_mv <<" time in the garage." << endl;
			}
			else
			{
				cout << "    car was moved " << pcar->no_mv <<" times in the garage." << endl;
			}

			D.pop_back(); 
			while(!S.empty())// moving from stack to deque after the right car has departed
			{
				//cout << "moving " << S.top().lp << "from stack to deque" << endl; 
				D.push_back(S.top());//the car on top of stack returns to deque
				S.pop();//deletes top car from stack


			}
			break;
		}
		else // else statement moving cars from deque to stack because they were not the car that was leaving
		{	
			//cout << "did not find, moving" << pcar->lp  << " from deque to stack" << endl;
			D.pop_back(); // pops of first in car
			pcar->no_mv++;//updates move count
			S.push(*pcar);//pushes car onto stack


		}

	}
	if (!found)// if statement for a car registered leaving that was not in the garage
	{
		cout <<	"No car with license plate \"" << lp << "\" is in the garage." << endl;
	}


}
