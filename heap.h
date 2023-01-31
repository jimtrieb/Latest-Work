
#include <assert.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef HEAP_H_
#define HEAP_H_

// data files

#define D1 "heap.d1"
#define D2 "heap.d2"
#define D3 "heap.d3"

#define INT_SZ 4   // width of integer
#define FLT_SZ 7   // width of floating-pt number
#define STR_SZ 12  // width of string

#define INT_LN 15  // no of integers in single line
#define FLT_LN 9   // no of floating-pt nums in single line
#define STR_LN 5   // no of strings in single line

// function and class prototypes

// stores items from input file into vector
template <typename T>
void get_list(vector<T>&, const char*);

// construct heap from items in vector
template <typename T, typename P>
void construct_heap(vector<T>&, P);

// class to print heap items

template <typename T>
class print_list {
  unsigned sz,  // heap size
      wid,      // min num of chars written in printout
      len,      // max num of items printed in single line
      cnt;      // counter for printout
 public:
  print_list(const unsigned& = 1, const unsigned& = 1, const unsigned& = 1, const unsigned& = 0);  // constructor
  void operator()(const T&);
};

//name: print_list
//use: constructor
//parameters: heap size, width, lenth, and a counter all designed to adjust output on std out
//returns: none
template <typename T> 
print_list<T>::print_list(const unsigned& s, const unsigned& w, const unsigned& l, const unsigned& c)
{
    //assignes each variable 
    this->sz = s;
    this->wid = w;
    this->len = l;
    this->cnt = c;
	
}

//name:operator
//use:overload, prints item x on std out
//parameters: const item x of type t 
//retuns: none
template <typename T>
void print_list<T>::operator()(const T& x)
{
	cout.width(wid); //output format 
	cout.precision(2);//output format
	cout << fixed << showpoint;
	cout << x << " ";
	cnt++; //update counter

	//if statemnt for determine a new line
	if (!(cnt % len) || (cnt == sz)) {
		cout << endl;
		if (cnt == sz) {
			cout << endl;
		}
	}
}

#endif  // HEAP_H_
