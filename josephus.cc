
#include<list>
#include<string>
#include<iostream>
#include<algorithm>
#include"josephus.h"
#include<iterator>
#include<cmath>
using namespace std;

//name: Suffix
//use: returns proper suffix for each number
//parameters: cnt variable which is the number of deletions
//returns: suffix corresponding to a number
string suffix(const unsigned &cnt)
{

	switch(cnt % 10) //switch statement for modulus division of cnt, determines which suffix to use
	{
		case 1: // case for the numbers 1 and 11
			if(cnt % 100  == 11)
			{
				return "th";
			}
			else
			{
				return "st"; //returns st for first value
			}
			break;
		case 2: //case for numbers 2 and 12
			if(cnt % 100 == 12) 
			{
				return "th";
			}
			else
			{
				return "nd"; //will return "nd" for second elimination
			}
			break;
		case 3: //case for numbers 3 and 13
			if(cnt % 100 == 13)
			{
				return "th";
			}
			else
			{
				return "rd";//will return "rd" for third elimination
			}
			break;
		default: //default case returns "th"
			return "th";
			break;

	}

}
//name: init_vals
//use: used to get user input from std in, and generate the list of names 
//parameters: list of strings, struct of the arugments given by std in
//retuns: none
void init_vals(list<string> &L, args &in)
{
	//gets number of people from std in stores in struct
	cout << "Number of people? ";	
	cin >> in.N;
	cout << in.N << endl;
	
	//gets index for elimination from std in stores in struct
	cout << "Index for elimination? "; 
	cin >> in.M;
	cout << in.M << endl;

	//gets index for printing from std in stores in struct
	cout << "Index for printing? ";
	cin >> in.K;
	cout << in.K << endl;
	
	//genteres the list L based of the number of people 
	SEQ s(in.N);
	L.resize(in.N);
	generate(L.begin(), L.end(), s);

}
//name: print_list
//use: to print the list of names before deletion, and then print eveytime after K number of deletions
//parameters: lsit of strings, cnt variable for number of deletions
//returns: none
void print_list(const list<string> &L, const unsigned &cnt)
{
	int counter = 1; //declares counter = 1
	cout << endl;
	if( cnt == 0) //if statement for if we have not eliminated anyone yet
	{
		cout << "Initial group of people" << endl;
		cout << "-----------------------" << endl;
	}
	else //else statment for printing list after every kth elimination
	{

		cout <<"After eliminating " << cnt << suffix(cnt) << " person"  << endl;
		cout <<"---------------------------";
		int digits_in_cnt = floor(log10(cnt)) + 1;
		//cout << digits_in_cnt << endl;
		for ( int q = 0; q < digits_in_cnt; q++)
		{
			cout << "-"; //based of number will print out how ever many -
		}
		cout << endl;
	}	
	//for loop declaring iterator to make sure std out only prints 12 names on each line
	for(list<string>::const_iterator it=L.begin(); it !=L.end(); ++it)
	{	

		cout << " " << *it;
		if( counter % 12 == 0)
		{
		       cout << endl;	
		}
		counter++; //update counter
	}
	cout << endl;
}


int main()
{
	list<string> L; //declare list of strings L
	unsigned cnt = 0;//initializes count to 0
	struct args args;//declare struct args

	init_vals(L,args); //calls init_vals to get arguments from std in and generate list
	print_list(L,cnt);//prints list of names
	int i = 0;

	//while loop for while the size of the list is not = to 0, an iterator will move through list and delete name based of argument given from struct args.
	while (L.size() != 0) 
	{

		int j = (i + (args.M - 1)) % L.size(); //j is index for elimination
		list<string>::iterator p=L.begin();//declares iterator p = to beggining of list
		advance(p, j);//advance funtion to move iterator p 
		L.erase(p); //erases element p
		cnt++;
		if ( cnt %args.K == 0 || L.size() == 1) // if statement to print out last person
		{
			print_list(L,cnt);
		}
		i = j; // updates i so j does not always start at beggining of list
	}
	return 0;
}
