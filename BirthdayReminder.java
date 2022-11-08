import java.util.Scanner; //import scanner 
import java.util.*;

public class BirthdayReminder 
{

	public static void main(String[] args) 
	{		
		Scanner input  = new Scanner(System.in); //scanner object to get user input
		
		ArrayList<String> names = new ArrayList<>(); //array list to hold names
		ArrayList<String> birthdays = new ArrayList<>(); //array list to hold birthdays
	
		int i = 0;
		while (i < 10) //add up to 10 people
		{	
			System.out.println("Enter a name or ZZZ to quit"); //get name
			String name = input.nextLine();
			if (name.equalsIgnoreCase("ZZZ")) //break if name = sentinel
			{
				break;
			}
			
			names.add(name); //add name to array list
			
			System.out.println("Enter a birthday"); //get birthday
			String birthday = input.nextLine();
			birthdays.add(birthday); //add birthday to array list
			System.out.println();
			i++; //increment counter
		}

		System.out.println();
		System.out.println("You entered " + i + " names"); //print out number of names entered
		
		for (int j = 0; j < names.size(); j++) //print out each name entered
		{
			System.out.println(names.get(j));
		}
		
		boolean keepGoing = true; //value used to determine if user will keep entering names
		
		System.out.println();
		System.out.println("Enter a name or ZZZ to quit"); //get name 
		String name = input.nextLine();
		
		if (name.equalsIgnoreCase("ZZZ")) //if entered sentinel value
		{
			keepGoing = false;
		}
		
		while (keepGoing)
		{
			boolean contains = names.contains(name); //determine if array has that name
			while (!contains) //if no entry for that name
			{
				System.out.println("You have not entered that name");
				System.out.println("Enter a name"); //get name 
				name = input.nextLine(); //get new name and check
				contains = names.contains(name);
			}
			
			int index = names.indexOf(name); //get index of name
			System.out.println();
			System.out.println("Name: " + names.get(index) + " Birthday: " + birthdays.get(index)); //print name and birthday
			System.out.println();
			
			System.out.println("Enter a name or ZZZ to quit"); //get name 
			name = input.nextLine();	
			if (name.equalsIgnoreCase("ZZZ")) //if entered sentinel value
			{
				break;
			}		
		}	

		input.close(); //close scanner
		
	} //end main

}// end class
