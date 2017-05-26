//CommandLineArguments.java
//Seongwoo Choi
//scho29
//CMPS 12B/M
//Laboratory Assignment 2

public class CommandLineArguments {
	public static void main(String[] args){
		int n = args.length;
		System.out.println("args.length = " + n);
		for(int i=0; i<n; i++) System.out.println(args[i]);
	}
}
