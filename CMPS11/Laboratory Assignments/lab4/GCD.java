
import java.util.Scanner;

class GCD{

	static boolean numberOrNot(String input)
	{
		try
		{
			Integer.parseInt(input);
		}
		catch(NumberFormatException ex)
		{
			return false;
		}
		return true;
	}

	public static void  main(String [] args)
	{
		int b;
		int d;
		Scanner input = new Scanner(System.in);
		System.out.print("Enter a positive integer: ");

		while(true){
			while( !input.hasNextInt() ){
				input.nextLine();
				System.out.print("Please enter a positive integer: ");
			}
			b = input.nextInt();
			if( b > 0 ) break;
			else {
				input.nextLine();
				System.out.print("Please enter a positive integer: ");
			}
		}
		System.out.print("Enter another positive integer: ");
		while(true) {
			while( !input.hasNextInt() ){
				input.nextLine();
				System.out.print("Please enter a positive integer: ");
			}
			d = input.nextInt();
			if( d > 0 ) break;
			else {
				input.next();
				System.out.print("Please enter a positive integer: ");
			}
		}

		System.out.println("The GCD of " + b + " and " + d + " is " +  getGcd(b,d) + ".");
	}


	public static int getGcd(int b, int d)
	{
		int gcd = 1;

		if(b>d)
		{
			for(int i = d; i >=1; i--)
			{
				if(b%i==0 && d%i ==0)
				{
					return i;
				}
			}
		}
		else
		{
			for(int j = b; j >=1; j--)
			{
				if(b%j==0 && d% j==0)
				{
					return j;
				}
			}
		}   
		return gcd;
	}



}

