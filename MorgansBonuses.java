import java.util.Scanner; //import scanner

public class MorgansBonuses 
{

	public static void main(String[] args) 
	{
		Scanner input  = new Scanner(System.in); //scanner object to get user input
		
		int choice; //determines if user wants to keep entering bonus factors
		
		int [][] bonusAmount = new int[7][5]; //array to hold bonuses
		
		//fill array
		bonusAmount[0][0] = 5;
		bonusAmount[0][1] = 9;
		bonusAmount[0][2] = 16;
		bonusAmount[0][3] = 22;
		bonusAmount[0][4] = 30;
		
		bonusAmount[1][0] = 10;	
		bonusAmount[1][1] = 12;
		bonusAmount[1][2] = 18;
		bonusAmount[1][3] = 24;
		bonusAmount[1][4] = 36;
		
		bonusAmount[2][0] = 20;
		bonusAmount[2][1] = 25;
		bonusAmount[2][2] = 32;
		bonusAmount[2][3] = 42;
		bonusAmount[2][4] = 53;
		
		bonusAmount[3][0] = 32;
		bonusAmount[3][1] = 38;
		bonusAmount[3][2] = 45;
		bonusAmount[3][3] = 55;
		bonusAmount[3][4] = 68;
		
		bonusAmount[4][0] = 46;
		bonusAmount[4][1] = 54;
		bonusAmount[4][2] = 65;
		bonusAmount[4][3] = 77;
		bonusAmount[4][4] = 90;
		
		bonusAmount[5][0] = 60;
		bonusAmount[5][1] = 72;
		bonusAmount[5][2] = 84;
		bonusAmount[5][3] = 96;
		bonusAmount[5][4] = 120;
		
		bonusAmount[6][0] = 85;
		bonusAmount[6][1] = 100;
		bonusAmount[6][2] = 120;
		bonusAmount[6][3] = 140;
		bonusAmount[6][4] = 175;
		
		do
		{
		
			System.out.println("How many full weeks did you work? 0-6+");
			int numWeeks = input.nextInt(); //get number of weeks worked
		
			while (numWeeks < 0) //get correct response
			{
				System.out.println("Please enter a positive number");
				numWeeks = input.nextInt();
			}
		
			if (numWeeks > 6) //working 6+ weeks is the same as 6
			{
				numWeeks = 6;
			}
		
			System.out.println("How many positive reviews did you receive? 0-4+");
			int numReviews = input.nextInt(); //get positive reviews gotten
		
			while (numReviews < 0) //get correct response
			{
				System.out.println("Please enter a positive number");
				numReviews = input.nextInt();
			}
		
		
			if (numReviews > 4) //4+ reviews is the same as 4
			{
				numReviews = 4;
			}
		
			int rowNum = 0;
			int colNum = 0;
		
			switch (numWeeks) //get row number for array
			{
				case 0:
					rowNum = 0;
					break;
				case 1:
					rowNum = 1;
					break;
				case 2:
					rowNum = 2;
					break;
				case 3:
					rowNum = 3;
					break;
				case 4:
					rowNum = 4;
					break;
				case 5:
					rowNum = 5;
					break;
				case 6:
					rowNum = 6;
					break;				
			}
		
			switch (numReviews) //get collumn number for array
			{
				case 0:
					colNum = 0;
					break;
				case 1:
					colNum = 1;
					break;
				case 2:
					colNum = 2;
					break;
				case 3:
					colNum = 3;
					break;
				case 4:
					colNum = 4;
					break;
			}
		
			//print bonus
			System.out.println("Your bonus is $" + bonusAmount[rowNum][colNum] + ".00");
			
			System.out.println();
			
			//determine if user wants to go again
			System.out.println("Would you like to enter more factors? (1 for yes) (any other integer for no)");
			choice = input.nextInt();
			
		} while (choice == 1); //loop while choice = 1
		
		
		input.close(); //close input
		
	} //end main

} //end class
