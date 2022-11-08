import java.text.DecimalFormat; //import decimal format
import java.text.NumberFormat; //import number format

public class Purchase 
{
	private double invoiceNumber; //invoice number
	private double amountOfSale; //price of sale before tax
	private double amountOfSalesTax; //sales tax
	private double totalPrice; //price of sale plus tax
	
	DecimalFormat df = new DecimalFormat("#.00"); //create decimal format
	NumberFormat formatter = NumberFormat.getCurrencyInstance(); //format print for money


	
	public void setInvoiceNumber(double invoiceNumber) //set method to set invoice number
	{
		this.invoiceNumber = invoiceNumber;
	}
	
	public void setAmountOfSale(double amountOfSale) //set method to set price of sale and determine tax and total price
	{
		this.amountOfSale = amountOfSale;
		
		amountOfSalesTax = amountOfSale * .05; //tax is 5%
		
		totalPrice = amountOfSalesTax + amountOfSale; //get total price
	}
	
	public void display() //display sale
	{
		System.out.println("Your invoice number is " + df.format(invoiceNumber));
		System.out.println("Your Price before tax is " + formatter.format(amountOfSale) + " dollars");
		System.out.println("Your sales tax is " + formatter.format(amountOfSalesTax) + " dollars");
		System.out.println("Your total price is " + formatter.format(totalPrice) + " dollars");

	}	    
}