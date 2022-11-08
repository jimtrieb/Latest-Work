import java.text.NumberFormat; //import format
import java.util.Scanner; //import scanner

public class TestApartments 
{

	public static void main(String[] args) 
	{
		Apartment apt1 = new Apartment(101, 2, 1, 725); //create apartment objects
		Apartment apt2 = new Apartment(102, 2, 1.5, 775);
		Apartment apt3 = new Apartment(103, 3, 2, 870);
		Apartment apt4 = new Apartment(104, 3, 2.5, 960);
		Apartment apt5 = new Apartment(105, 3, 3, 1100);
		
		int minNumOfBedrooms; //user minimum # of bedrooms
		double minNumOfBaths; //user minimum # of baths
		int maxRent; //user max rent
		
		Scanner input  = new Scanner(System.in); //scanner object to get user input
		NumberFormat formatter = NumberFormat.getCurrencyInstance(); //format print for money
		
		System.out.println("What is the minimum number of bedrooms you want");
		minNumOfBedrooms = input.nextInt(); //get minimum bedrooms
		
		System.out.println("What is the minimum number of bathrooms you want");
		minNumOfBaths = input.nextDouble(); //get minimum baths
		
		System.out.println("What is the maximun rent you will pay");
		maxRent = input.nextInt(); //get max rent
		
		//determine if apt1 meets criteria and if it does print info
		if (apt1.getNumBaths() >= minNumOfBaths && apt1.getNumBedrooms() >= minNumOfBedrooms && apt1.getRentAmt() <= maxRent)
		{
			System.out.println("Apartment 1 has " + apt1.getNumBaths() + " baths, " + apt1.getNumBedrooms() + " bedrooms, and cost " + formatter.format(apt1.getRentAmt()) + " dollars");
		}
		
		else //apt 1 does not meet standards
		{
			System.out.println("Apartment 1 does not meet your criteria");
		}

		//determine if apt2 meets criteria and if it does print info
		if (apt2.getNumBaths() >= minNumOfBaths && apt2.getNumBedrooms() >= minNumOfBedrooms && apt2.getRentAmt() <= maxRent)
		{
			System.out.println("Apartment 2 has " + apt2.getNumBaths() + " baths, " + apt2.getNumBedrooms() + " bedrooms, and cost " + formatter.format(apt2.getRentAmt()) + " dollars");
		}
		
		else //apt 2 does not meet standards
		{
			System.out.println("Apartment 2 does not meet your criteria");
		}

		//determine if apt3 meets criteria and if it does print info
		if (apt3.getNumBaths() >= minNumOfBaths && apt3.getNumBedrooms() >= minNumOfBedrooms && apt3.getRentAmt() <= maxRent)
		{
			System.out.println("Apartment 3 has " + apt3.getNumBaths() + " baths, " + apt3.getNumBedrooms() + " bedrooms, and cost " + formatter.format(apt3.getRentAmt()) + " dollars");
		}
		
		else //apt 3 does not meet standards
		{
			System.out.println("Apartment 3 does not meet your criteria");
		}

		//determine if apt4 meets criteria and if it does print info
		if (apt4.getNumBaths() >= minNumOfBaths && apt4.getNumBedrooms() >= minNumOfBedrooms && apt4.getRentAmt() <= maxRent)
		{
			System.out.println("Apartment 4 has " + apt4.getNumBaths() + " baths, " + apt4.getNumBedrooms() + " bedrooms, and cost " + formatter.format(apt4.getRentAmt()) + " dollars");
		}
		
		else //apt 4 does not meet standards
		{
			System.out.println("Apartment 4 does not meet your criteria");
		}

		//determine if apt5 meets criteria and if it does print info
		if (apt5.getNumBaths() >= minNumOfBaths && apt5.getNumBedrooms() >= minNumOfBedrooms && apt5.getRentAmt() <= maxRent)
		{
			System.out.println("Apartment 5 has " + apt5.getNumBaths() + " baths, " + apt5.getNumBedrooms() + " bedrooms, and cost " + formatter.format(apt5.getRentAmt()) + " dollars");
		}

		else //apt 5 does not meet standards
		{
			System.out.println("Apartment 5 does not meet your criteria");
		}
			
		input.close(); //close scanner
	} //end main

} //end TestApartments class
