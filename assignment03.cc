/*
CSCI 340, Assignment03, Fall 2020
Jim Trieb
z1912658
0PE1
Mohith Koppisetti, Palak Jalota
9-21-2020
Find all prime numbers from 2 to user input
*/

#include <iostream>
#include <set>
#include <iterator>
#include <cmath>
#include <iomanip>
using namespace std;
using std::set;

/*
Function name: Sieve
Parameters: set of integers and an int
returns: none
use: an algorithm to get all the prime numbers from 2 to the user input
*/
void sieve(set<int>& s, int n)    //Algorithm for finding prime numbers
{
	set <int>  :: iterator itr;  //declaring iterator
	
	for (itr = s.begin(); itr != s.end(); ++itr) //for loop to iterate over set
	{
		int prime  = *itr;
		for (int k = prime * 2; k <= n; k += prime)  //for loop to remove multiples of k
	       	{
			s.erase(k);
		}
	}
}

/*
Function name: Print Primes
Parameters: set of integers
returns: none
use: Prints the set to std out
*/
void print_primes(const set<int>& s)
{
	int counter = 0; //declaring counter for items per line

	set <int>  :: iterator itr; //declaring iterator
	
	for (itr = s.begin(); itr != s.end(); ++itr)//for loop that iterates over set
	{
		cout << setw(5) << *itr;//set width of std out and print set elements
		counter++; //increment counter

		if(counter == 16)//when counter = 16 we reset it to 0
		{
			cout << endl;
			counter = 0;
		}
	}

	cout << endl;

}

int
main()
{	
	int upper_limit;

	std::cout << "Upper limit for the set of primes: ";
	cin >> upper_limit; //get n value
	set <int>  s1;//create set

	for( int i = 2; i <= upper_limit; i++)//for loop to give set its elements
	{
		s1.insert(i);
	}
	
	cout << endl;
	sieve(s1, upper_limit);	//call algorith and print functions
	print_primes(s1);	
	
	
	return 0;
}
