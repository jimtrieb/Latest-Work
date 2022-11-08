
public class Factorials 
{

	//function to calculate factorial recursively, takes an int passed in and returns an int
	//keeps adding to return value to find factorial
	public static int findFactorial(int n)
	{
		if (n == 0) //multiply by 1 at end
		{
			return 1;
		}
		
		else
		{
			return (n * findFactorial(n-1)); //return (number passed in * number - 1) will execute until number = 0
		}
	} //end factorial function
	
	
	public static void main(String[] args) 
	{
		for (int i = 1; i <= 10; i++) //loop to use the numbers 1-10
		{
			System.out.println("The factorial of " + i + " is " + findFactorial(i)); //call findFactorial on numbers 1-10 and print
		}

	} //end main

} //end class factorials
