/* Lawn.java
 * Seongwoo Choi
 * scho29
 * Programming Assignment 1
 *
 */

import java.util.Scanner;

class Lawn {
	public static void main( String[] args) {
		double lengthLot, widthLot;
		double lengthHouse, widthHouse;
		double mowRate;
		double area;
		int h, m, s;

		Scanner sc = new Scanner(System.in);

		System.out.print("Enter the length of the lot, in feet: ");
		lengthLot = sc.nextDouble();
		System.out.print("Enter the width of the lot, in feet: ");
		widthLot = sc.nextDouble();

		System.out.print("Enter the length of the house, in feet: ");
		lengthHouse = sc.nextDouble();
		System.out.print("Enter the width of the house, in feet: ");
		widthHouse = sc.nextDouble();
		area = lengthLot*widthLot-lengthHouse*widthHouse;
		System.out.println("The lawn area is " + area + " square feet.");
		System.out.print("Enter the mowing rate, in square feet per second: ");
		mowRate = sc.nextDouble();
		System.out.print("The mowing time is ");
		s = (int) Math.round(area/mowRate);
		m = s/60;
		s = s%60;
		h = m/60;
		m = m%60;
		System.out.println(h + " hour" + (h == 1 ? " " : "s ") + m + " minute" + (m == 1 ? " " :"s ") + s + " second" + (s == 1 ? "" : "s"));
	}
}
