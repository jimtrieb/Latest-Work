import java.util.Scanner; //import scanner

public class TimesAndInstructors 
{

	public static void main(String[] args) 
	{
		Scanner input  = new Scanner(System.in); //scanner object to get user input
		
		String [][] classList = new String[5][3]; //array to hold classes
		
		//initialize array
		classList[0][0] = "CIS 101";
		classList[0][1] = "Mon 9 am";
		classList[0][2] = "Farrell";
		
		classList[1][0] = "CIS 210";
		classList[1][1] = "Mon 11 am";
		classList[1][2] = "Patel";
		
		classList[2][0] = "MKT 100";
		classList[2][1] = "Tues 830 am";
		classList[2][2] = "Wong";
		
		classList[3][0] = "ACC 150";
		classList[3][1] = "Tues 6 pm";
		classList[3][2] = "Deitrich";
		
		classList[4][0] = "CIS 101";
		classList[4][1] = "Fri 1 pm";
		classList[4][2] = "Lenno";
		
		
		System.out.println("Enter a class to search for");
		String name = input.nextLine(); //get class user wants
		
		
		
		boolean contains = false; //holds status of if class is available	

		for (int i = 0; i < classList.length; i++) //search array
		{
			for (int j = 0; j < classList[i].length; j++)
			{
				if (classList[i][j].equalsIgnoreCase(name)) //if index matches class name print infro
				{
					System.out.println("Course: " + classList[i][j] + " Time: " + classList[i][j + 1] + " Instructor: " + classList[i][j + 2]);
					contains = true; //school offers class
				}
			}
		}
		
		if (!contains) //print if not class available
		{
			System.out.println("We do not have that class available");
		}
		
		input.close(); //close scanner
	} //end main
} //end class
