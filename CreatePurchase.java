import java.util.Scanner; //import scanner
 
public class CreatePurchase 
{

	public static void main(String[] args) 
	{
		Scanner input  = new Scanner(System.in); //scanner object to get user input
		
		Purchase p1 = new Purchase(); //create purchase object
		
		System.out.println("What is your invoice number (1000 - 8000)"); //ask for invoice number
		double invoiceNumber = input.nextDouble();
		
		while (invoiceNumber < 1000 || invoiceNumber > 8000) //get correct value if entered incorrectly
		{
			System.out.println("Please enter correct number (1000 - 8000)");
			invoiceNumber = input.nextDouble();
		}
		
		System.out.println("What is your sale amount (non-negative)"); //ask for sale amount
		double saleAmount = input.nextDouble();
		
		while (saleAmount < 0) //get a non-negative sale amount
		{
			System.out.println("Please enter a non-negative amount");
			saleAmount = input.nextDouble();
		}
		
		p1.setInvoiceNumber(invoiceNumber); //set the invoice number
		p1.setAmountOfSale(saleAmount); //set the sale amount and calculate tax and total
		p1.display(); //display sale details
		
		
		
		input.close();
	} //end main

} //end create purchase class
