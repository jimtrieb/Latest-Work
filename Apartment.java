
public class Apartment 
{
	private int aptNumber; //apartment number
	private int numBedrooms; //number of bedrooms
	private double numBaths; //number of baths
	private int rentAmt; //rent amount
	
	public Apartment(int aptNumber, int numBedrooms, double numBaths, int rentAmt) //constructor to initialize values
	{
		this.aptNumber = aptNumber;
		this.numBedrooms = numBedrooms;
		this.numBaths = numBaths;
		this.rentAmt = rentAmt;
	}
	
	public int getAptNumber() //get method to return apartment number
	{
		return aptNumber;
	}
	
	public int getNumBedrooms() //get method to return number of bedrooms
	{
		return numBedrooms;
	}
	
	public double getNumBaths() //get method to return number of baths
	{
		return numBaths;
	}
	
	public int getRentAmt() //get method to return rent amount
	{
		return rentAmt;
	}
} //end class apartment
