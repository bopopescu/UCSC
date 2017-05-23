//  Roots.java
//  Seongwoo Choi 
//  scho29
//  Programming Assignment 4
//  This is a java program that determines the real roots of a polynomial lying within a specified range.


import java.util.Scanner;

class Roots{

   static double poly(double[] C, double x){
      double sum = 0;
      for(int i=0; i<C.length; i++){
         sum += C[i]*Math.pow(x,i);  
      }
      return sum;
   }
   
   static double[] diff(double[] C){
      double[] D = new double[C.length];
      for(int i=0; i<C.length; i++){
         D[i] = C[i]*i;
      }
      return D;
   }

   static double findRoot(double[] C, double a, double b, double tolerance){
      double root = 0.0;
      while(b-a > tolerance){   
         root = (a+b)/2.0;
         if(poly(C, a)/poly(C, root) < 0){ 
            b = root;
         }
         else if (poly(C, b)/poly(C, root) < 0){
            a = root;
         }
      }
      return root;
   }

   public static void main(String[] args){
      Scanner sc = new Scanner(System.in); 
      double resolution = Math.pow(10,-2);
      double tolerance = Math.pow(10,-7);
      double threshold = Math.pow(10,-3);
      boolean root = false;
      System.out.print("Enter the degree: ");
      int n = sc.nextInt(); 
      int degree = n+1;
      System.out.print("Enter "+degree+" coefficients: ");
      double[] coe = new double[degree];
      for(int i=0; i<degree; i++){
         coe[i] = sc.nextDouble();
      } 
      System.out.print("Enter the left and right endpoints: ");
      double L = sc.nextDouble();
      double R = sc.nextDouble();
      double deriv[] = diff(coe);
      for(double i = L; i<R; i += resolution){
         if(poly(coe, i)/poly(coe, i+resolution) <0){
            double x = findRoot(coe, i, i+resolution, tolerance);
            String oddRoot = String.format("%.6g%n", x);
            System.out.print("Root found at: " +oddRoot);
            root = true;
         }
         else if(poly(deriv, i)/poly(deriv, i+resolution)<0){
            double y = findRoot(deriv, i, i+resolution, tolerance);
            if (Math.abs(poly(coe, y)) < threshold) {
               String oddRoot2 = String.format("%.6g%n",y);
               System.out.print("Root found at: " +oddRoot2);
               root = true;
            }
         }
      }
      if(!root) System.out.println("No roots were found.");
   } 
}
