

#include "heap.h"
#include <istream>

//name: get_list
//use: gets the list from a file and puts into a vector
//parameters: vector v and path name of file
//returns: none
template <typename T>
void get_list(vector<T> &v, const char *path) {
  // Your implementation goes here!!!
  v.clear();
  T read_in; //variable of type t that we are reading in
  ifstream myfile (path); //create ifstream using path as file we want to read
  while(1)
  {
	
	myfile >> read_in; //read from myfile to read in

	//if statement for reaching end of file
	if(myfile.eof())
	{
		break;
	}

	v.insert(v.end(), read_in); //insert what we read into vector
  }
 myfile.close(); //close file 

}

//name: construct_heap
//use: creates the heap using the vector and stl functions
//parameters: vector and predicate
//returns: none
template <typename T, typename P>
void construct_heap(vector<T> &v, P pred) {
  // Your implementation goes here!!!

	make_heap(v.begin(), v.end(),pred); //makes the heap
	sort_heap(v.begin(), v.end(), pred); //sorts heap
}

int main() {
  vector<int>    v1;  // heap of integers
  vector<float>  v2;  // heap of floating-pt nums
  vector<string> v3;  // heap of strings

  // print header message
  cout << "\t\t\t*** Heaps and Heapsort - Output ***\n\n";

  // first heap

  cout << "first heap - ascending order:\n\n";
  get_list(v1, D1);
  construct_heap(v1, less<int>());
  print_list<int> print1(v1.size(), INT_SZ, INT_LN);
  for_each(v1.begin(), v1.end(), print1);

  cout << "first heap - descending order:\n\n";
  get_list(v1, D1);
  construct_heap(v1, greater<int>());
  for_each(v1.begin(), v1.end(), print1);

  // second heap

  cout << "second heap - ascending order:\n\n";
  get_list(v2, D2);
  construct_heap(v2, less<float>());
  print_list<float> print2(v2.size(), FLT_SZ, FLT_LN);
  for_each(v2.begin(), v2.end(), print2);

  cout << "second heap - descending order:\n\n";
  get_list(v2, D2);
  construct_heap(v2, greater<float>());
  for_each(v2.begin(), v2.end(), print2);

  // third heap

  cout << "third heap - ascending order:\n\n";
  get_list(v3, D3);
  construct_heap(v3, less<string>());
  print_list<string> print3(v3.size(), STR_SZ, STR_LN);
  for_each(v3.begin(), v3.end(), print3);

  cout << "third heap - descending order:\n\n";
  get_list(v3, D3);
  construct_heap(v3, greater<string>());
  for_each(v3.begin(), v3.end(), print3);

  // print termination message
  cout << "\t\t\t*** end of program execution ***\n\n";
  return 0;
}
