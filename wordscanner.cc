/*
CSCI 340, Assignment 4, Fall 2020
Jim Trieb
z1912658
PE1
Mohith Koppisetti,Palak Jalota
10-5-2020
Recieve a string of words and rid it of punctuation
*/
#include <map>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void get_words(map<string, int>&);

void print_words(const map<string, int>&);

void clean_entry(const string&, string&);


int main()
{

	map<string, int> words; //create a map called words
	get_words(words);// pass map to get words and print words functions
	print_words(words);



	return 0;
}
//Function: get_words
//Use: To get words from input, in this case pipe from wordscanner.in
//parameters: a map of strings and int key 
//returns: nothing 
//notes: Will call clean_entry function to clean the input stream
void get_words(map<string, int>& sorted_words)
{
	string cleaned;//stream of words after clean entry function is called 
	string str;//original stream of words
	cin >> str;
	while(!cin.eof())//while loop that goes until end of input file
	{
		clean_entry(str, cleaned);//clean entry function that passes the cleaned string to sorted words map
		//cout << "[" << str << "] ["  << cleaned << "]" << endl;
		if(cleaned.length() != 0)
		{
			sorted_words[cleaned]++;
		}
		cin >> str;
	}


}
//Function:print words
//use: print the input stream after removed punctuation to cout
//parameters: a map
//returns: nothing
void print_words(const map<string, int>& sorted_words)
{
	int NO_ITEMS = 3;// set number of items per line
	int ITEM_W = 16;//set width
	int counter = 0;

	map<string, int>::const_iterator it = sorted_words.begin();// creates iterator to = beginning of map

	while(it != sorted_words.end())//iterator iterates through map
	{
		for( int x = 0; x < NO_ITEMS; x++)
		{
			cout << left << setw(ITEM_W) << it->first << ": " << setw(5) << it->second << " ";
			counter += it->second;
			it++;
			if(it == sorted_words.end())
			{
				break;
			}
		}
		cout << endl;
	}
	
	cout << endl << "no of words in input stream  :" << counter << endl;
	cout << "no of words in output stream :" << sorted_words.size() << endl;
}
//function: clean entry
//use: Clean the input stream of certain punctuation marks
//parameters: 2 strings
//returns: nothing
void clean_entry(const string& input, string& output)
{
	int start = -1;
	int end = -1;
	for( int i = 0; i < input.length(); i++)//for loop that goes through original input string
	{
		if(isalnum(input[i]))//isalnum algorithm to keep numbers and letters
		{
			if(-1 == start) // if and else statements to update string if a isalnum character was detected 
			{
				start = i;
				end = i;
			}

			else
			{
				end = i;
				
			}
		}

		else
		{	
			if(start > -1)
			break;
		}

	}

	if(start == -1)
	{
		output = "";
	}

	else
	{
		
		output = input.substr(start, end - start + 1);
		for( int i = 0; i < output.length(); i++)//for loop to change all letters to lowercase
		{
			output[i] = tolower(output[i]);
		}

	}

	

}
