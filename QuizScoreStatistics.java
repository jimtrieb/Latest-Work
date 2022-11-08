import java.text.DecimalFormat; //import decimal format
import java.util.Scanner; //import scanner

public class QuizScoreStatistics 
{

	public static void main(String[] args) 
	{
		Scanner input  = new Scanner(System.in); //scanner object to get user input
		DecimalFormat df = new DecimalFormat("#.00"); //create decimal format
		
		int amountOfScores = 0; //holds number of quiz scores entered
		double totalScore = 0; //holds sum of scores used to get average
		
		System.out.printf("Enter quiz score (99 to stop) "); 
		double number = input.nextDouble(); //get user input and store
		
		if (number != 99) //if they dont enter 99 first
		{
			
			while (number < 0 | number > 10) //if user enters invalid quiz score ask them to re-enter
			{
				System.out.printf("Please enter correct score ");
				number = input.nextDouble();
			}
			
			double smallNum = number; //first number is always the smallest
			double largeNum = number; //first number always the biggest

		
			while (number != 99) //take in numbers until user enters 99
			{
				
				while (number < 0 | number > 10) //if user enters invalid quiz score ask them to re-enter
				{
					System.out.printf("Please enter correct score ");
					number = input.nextDouble();
					
					if (number == 99) //case if user enters wrong quiz score then enters wants to quit
					{
						break;
					}
				}				
				
				if (number == 99) //break if user enters 99
				{
					break;
				}
				
				
				
				amountOfScores++; //increment amount of scores by 1
				totalScore += number; //running total of scores
				
				if (smallNum > number)
				{
					smallNum = number; //if smallest num is greater than new number assign smallest num to new number
					
				}
			
				if (largeNum < number)
				{
					largeNum = number; //if largest num is smaller than new number assign largest num to new number
				}
			
				System.out.printf("Enter quiz score (99 to stop) ");
				number = input.nextDouble(); //enter next number 
				
			}
			
			System.out.println("*********************************"); //header
			System.out.println("The lowest quiz score is " + df.format(smallNum)); //print smallest number
			System.out.println("The highest quiz score is " + df.format(largeNum)); //print largest number
			System.out.println("You entered " + amountOfScores + " scores"); //print number of scores entered
			System.out.println("The total score is " + df.format(totalScore)); //print the total sum of scores
			System.out.println("The average quiz score is " + df.format(totalScore / amountOfScores)); //print average of scores
		}

		else //if user entered 99 first
		{
			System.out.println("No numbers entered");
		}

		input.close(); //close input

	} //end main

} //end class
