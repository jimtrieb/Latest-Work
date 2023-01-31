
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <set>
#include <sstream>


using namespace std;



int countSubString(string file, string searchString) //function to read a file and keep track how many times a substring is found
{

	int timesFound = 0; //times substring was found in file

	for (size_t offset = file.find(searchString); offset != std::string::npos; offset = file.find(searchString, searchString.length() + offset))
	{
	     	timesFound++;
	}


	return timesFound;

}


int countUniqueString(string fileContents, string searchString) //stores into a set a unique string
{

	set <string> uniqueValues; //set to contain unique strings in a line

	string line;
	stringstream file(fileContents);

	while (getline(file, line))
	{
		if (line.find(searchString) != std::string::npos)
		{
			uniqueValues.insert(line);
		}

	}


	return uniqueValues.size();
}


string readFile(const string fileName) //reads a file, parameter passed from source code not by command line
{

	string line;
	string linesRead;
	ifstream file (fileName);
	if (file.is_open())
	{
		while (getline (file, line))
		{
			linesRead.append(line);
			linesRead.append(".");
			linesRead.append("\n");

		}

		file.close();
	}
	
	return linesRead; //return the lines read from file stored into a string created
}


string processorData(string fileContents, string subString)
{
	size_t offset = fileContents.find(subString);
	int firstCharacterOfReturnValue = offset + subString.length();
	offset = fileContents.find("\n", firstCharacterOfReturnValue);
	return fileContents.substr(firstCharacterOfReturnValue, offset - firstCharacterOfReturnValue);	


}


string getFieldFromLine(string lineContents, int fieldNumber) 
{
	//line has fields separated by spaces
	stringstream ss(lineContents);
	string mystring; //string to hold field
	while (fieldNumber-- > 0)
	{
		getline(ss, mystring, ' ');
	}

	return mystring;

}


int jtos(string s) //convert to seconds	
{
	return (stoi(s) / 100);
	
}

int stod(int i) //seconds to days
{
	return (i / 86400);
}

int stoh(int i) //seconds to hours
{
	return ((i % 86400) / 3600);
}

int stom(int i) //seconds to minutes
{
	i = i % (24 * 3600);
	i %= 3600;
	return i / 60;
}

int stos(int i) //get remaining seconds
{
	return (i % 60);
}

string getSwapDeviceSize(string fileContents)
{
	string line;
	stringstream mystream(fileContents); //need string stream for getline

	getline(mystream, line);
	getline(mystream, line);

	size_t offset = line.find("\t");
	offset = line.find_first_of("0123456789", offset);
	size_t endOffset = line.find("\t", offset);

	return line.substr(offset, endOffset - offset);

}


int main()
{

	int numberProcessors; //number of processors
	int physicalMulti; //number of physical multi-core chips

	cout << "A. Questions about turing's OS." << endl;
	cout << "\t1. Turings ostype is " << readFile("/proc/sys/kernel/ostype");
	cout << "\t2. Turings hostname is " << readFile("/proc/sys/kernel/hostname");
	cout << "\t3. Turings osrelease is " << readFile("/proc/sys/kernel/osrelease");
	cout << "\t4. Turings version is " << readFile("/proc/sys/kernel/version") << endl;

	string procCPU = readFile("/proc/cpuinfo"); //string containing /proc/cpuinfo file
	string procStat = readFile("/proc/stat"); //string containing /proc/stat file

	numberProcessors = countSubString(procCPU, "processor");
	physicalMulti = countUniqueString(procCPU, "physical id");

	string procUpTime = readFile("/proc/uptime"); //read contents of /proc/uptime store in string
	string procSwaps = readFile("/proc/swaps"); //read contents of /proc/swaps store in string


	string upTime = getFieldFromLine(procUpTime, 1);
	cout << "B. Questions about turing's processor:\n";
	cout << "\t1. Turing has " << numberProcessors << " processors. " << endl;
	cout << "\t2. Turing has " << physicalMulti << " physical multi-core chips. " << endl;
	cout << "\t3. Turing has been up for " << upTime << " seconds. " << endl;
	int intUpTime = stoi(upTime); //convert uptime from string to int
	cout << "\t4. Turing has been up for " 
		<< stod(intUpTime) 
		<< " days, " 
		<< stoh(intUpTime) 
		<< " hours, " 
		<< stom(intUpTime) 
		<< " minutes, " 
		<< stos(intUpTime)
		<< " seconds."
		<< endl;
	cout << endl;


	

	cout << "C. For processor 0, answer these questions:" << endl;
	cout << "\t1. Processor 0's vendor is " << processorData(procCPU, "vendor_id	: ") << endl;
	cout << "\t2. Processor 0's model name is " << processorData(procCPU, "model name	: ") << endl;
	cout << "\t3. Processor 0's address sizes are " << processorData(procCPU, "address sizes	: ") << endl;
	cout << endl;

	string cpu0Stats = processorData(procStat, "cpu0 "); //gets info on cpu 0

	cout << "D. For processor 0, answer these questions:\n";
	cout << "\t1. Processor 0 has been in user mode for " <<  jtos(getFieldFromLine(cpu0Stats, 1)) << " seconds."<< endl;
	cout << "\t2. Processor 0 has been in system mode for " <<  jtos(getFieldFromLine(cpu0Stats, 3)) << " seconds." << endl;
	int idleTime = jtos(getFieldFromLine(cpu0Stats, 4));
	cout << "\t3. Processor 0 has been idle for " <<  idleTime << " seconds. " << endl;
	cout << "\t4. Processor 0 has been idle for " 
		<< stod(idleTime) 
		<< " days, " 
		<< stoh(idleTime) 
		<< " hours, " 
		<< stom(idleTime) 
		<< " minutes, " 
		<< stos(idleTime)
		<< " seconds."
		<< endl;
	cout << endl;

	double swapSize = stoi(getSwapDeviceSize(procSwaps)) / 1024;

	cout << "E. Turings swap device is " << swapSize << " mb." << endl;




	return 0;
}
