//Seongwoo Choi//
//scho29
//CMPS 11
//Programming Assignment 2

import java.util.Scanner;

class Guess {
	public static void main(String[] args) {
		int random =(int)(Math.random()*10)+1;
		int counter = 0;
		int userInput;
		Scanner sc = new Scanner(System.in); 		

		System.out.println();
		System.out.println("I'm thinking of an integer in the range 1 to 10. You have three guesses.");
		System.out.println();

		while (counter < 3) {

			System.out.print("Enter your ");
			if (counter == 0)
				System.out.print("first guess: ");
			else if(counter == 1)
				System.out.print("second guess: ");
			else if(counter == 2)
				System.out.print("third guess: ");
			userInput = sc.nextInt ();
			if (random < userInput)
				System.out.println("Your guess is too high.");
			else if (random > userInput)
				System.out.println("Your guess is too low.");
			else if (random == userInput) {
				System.out.println("You win!");
				System.out.println();
				return;
			}
			System.out.println();

			counter += 1;
		}
		System.out.println("You lose.  The number was " + random);
		System.out.println();
	}
}
