//***************************************************************************
//
//  Jim Trieb
//  z1912658
//  csci463 PE1
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************
#include <iostream>
#include <stdint.h>
#include <iomanip>
using namespace std;


/**
 * Will call each print function below to do the decoding and printing of hex values in one step
 *
 * @param x the hex value read in from std in
 *
 * @note only use of this functions is to call every other one
 *******************************************************************/
void printBinFloat(uint32_t x);



/**
 * prints the binary value of each hex number read in
 *
 * @param hexVal hex value read in from std in
 *******************************************************************/
void printBinary(uint32_t hexVal);


/**
 * prints sign of hex value read in 
 *
 * @param hexVal hex value read in from std in
 *
 * @return will return 1 if sign positive or 0 if sign negitive
 *******************************************************************/
int  printSign(uint32_t hexVal);


/**
 * prints exponent in IEEE format and its deciaml equivilant
 *
 * @param hexVal hex value read in from std in
 *
 * @return the decimal exponent
 *
 * @note decimal exponent is printed out by unsetting hex state flag
 *******************************************************************/
int32_t printExponent(uint32_t hexVal);



/**
 * prints significand of hex value read in
 *
 * @param hexVal hex value read in from std in
 *
 * @return significand 
 *******************************************************************/
uint32_t printSignificand(uint32_t hexVal);




/**
 * prints out full value of initial hex value read in
 *
 * @param hexVal hex value read in from std in
 * @param sign the sign of the hex value
 * @param exponent the exponent of hex value
 * @param significand the significand of hex value
 *
 * @note need to pass in value, sign, exponent and significand to calculate full value
 ***************************************************************************************/
void printFull(uint32_t hexVal, int sign, int32_t exponent, uint32_t significand);




int main()
{

	uint32_t hexValue; //value hex digits will be read into

	while (cin >> hex >> hexValue) //while loop to print output each time you have new data to read
	{
		printBinFloat(hexValue);
	}
	return 0;
}

void printBinFloat(uint32_t x)
{
	//calls to each function for decoding and printing
	printBinary(x);

	int sign = printSign(x);

	int32_t exponent = printExponent(x);

	uint32_t significand = printSignificand(x);

	printFull(x, sign, exponent, significand);
}


void printBinary(uint32_t hexVal)
{
	int counter = 0; //counter used for printing digits in groups of 4 

	cout << "0x" << setfill('0') << setw(8) << hex << hexVal << " ="; //print hex value from input

	uint32_t bitMask = 0x80000000; //setting msb 

	while (bitMask > 0) //go until 32 comparisons
	{

		if ((counter++ % 4) == 0) //if statement used to specify output, cout space when counter is a multiple of 4
		{
			cout << " ";
		}
		
		if ((bitMask & hexVal) == 0) // if statement using an and mask used to determine output of hex number in binary 
		{
			cout << "0";
		}

		else
		{
			cout << "1"; //both bits on
		}

		bitMask = bitMask >> 1; //shift bitMask right one to mask next hex digit
	}

	cout << endl; 
	
}

int printSign(uint32_t hexVal)
{
	uint32_t signMask = 0x80000000; //mask to check sign bit

	if ((signMask & hexVal) == 0)
	{
		cout << "sign: 0" << endl;
		return 0;
	}
	else
	{
		cout << "sign: 1" << endl;
		return 1;
	}

}

int32_t printExponent(uint32_t hexVal)
{
	uint32_t exponentMask = 0x7f800000; //mask to get only exponent bits

	int32_t exponent = ((exponentMask & hexVal) >> 23) - 127; //shift exponent bits down converts to IEEE exponent

	cout << " exp: 0x" << setfill('0') << setw(8) << hex << exponent; //print out exponent in hex

	cout.unsetf(ios_base::hex); //unsetting hex state flag in cout

	cout << " (" << exponent << ")"; //print out exponent as int

	cout << endl;

	return exponent; 

}

uint32_t printSignificand(uint32_t hexVal)
{
	uint32_t significandMask = 0x007fffff; //mask to compare with significand, turns of sign and exponent bits

	cout << " sig: 0x" << setfill('0') << setw(8) << hex << (significandMask & hexVal); //print out significand

	cout << endl;

	return (significandMask & hexVal); //returns significand
}

void printFull(uint32_t hexVal, int sign, int32_t exponent, uint32_t significand) 
{
	uint32_t mask = 0x00400000; //gets high order bit of significand

	switch(hexVal) //switch statement to handle special cases +- 0 and +-inf
	{
		case 0x7f800000: //sign:0 exp: 128 sig: 0 //positive infinity case
			cout << "+inf" << endl;
			break;

		case 0xff800000: //sign:1 exp: 128 sig 0 //negative infinity case
			cout << "-inf" << endl;
			break;

		case 0x00000000: //sign 0 exp: -127 sig 0 //positive 0 case
			cout << "+0" << endl;
			break;

		case 0x80000000: //sign 1 exp: -127 sig 0 //negative 0 case
			cout << "-0" << endl;
			break;

		default: //handle general case
			if (sign == 1) //determines sign of full value
			{
				cout << "-";
			}
			else
			{
				cout << "+";
			}
			if (exponent >= 0) //if statement if exponent is positve
			{ 
				cout << "1"; //implied 1

				int digitsBeforeDecimal; //digits of significand before decimal

				if (exponent < 23) // how many digits of significand are before decimal? 
				{
					digitsBeforeDecimal = exponent; //just the number the exponent shifts up
				}
			       	else
			       	{
					digitsBeforeDecimal = 23; //all of them, may also need filler 0's
				}
				int fillerZeroes = exponent - 23; //counts filler zeroes. dont care if negative

				int digitsAfterDecimal = 23 - digitsBeforeDecimal; //rest of significand digts go after decimal

				for (int i=0; i<digitsBeforeDecimal; i++) //print out significand digits
				{
					
					if ((mask & significand) > 0) 
					{							
						cout << "1";
					}
					else
					{
						cout << "0";
					}
					mask = mask >> 1; //shift right 1
				}

				for (int i=0;i<fillerZeroes;i++) //does nothing if negative
				{
					cout << "0";
				}

				cout << ".";

				if (digitsAfterDecimal == 0) //place holder zero
			       	{
					cout << "0";
				}

				else
			       	{
					for (int i=0 ;i<digitsAfterDecimal ;i++) //print out remaining digits of significand
				       	{	
						if ((mask & significand) > 0)
						{							
							cout << "1";
						}
						else
						{
							cout << "0";
						}
						mask = mask >> 1;
					}						
				}						
			}

			else //case for negative exponent
			{
				cout << "0."; //initial 0

				int fillWithZeroes = (-exponent) - 1; 

				for (int i=0; i<fillWithZeroes ;i++)
			       	{
					cout << "0";
				}

				cout << "1"; //implied 1

				for (int i=0; i<23; i++) //prints out significand
				{
					if ((mask & significand) > 0) //if both bits on
					{							
						cout << "1";
					}
				        else
				        {
						cout << "0";
					}
					mask = mask >> 1; //shift mask right 1
				}
			}

			cout << endl;

			break;
	}
}
