import java.util.Scanner;

class FindRoot{
   public static void main(String[] args){
   Scanner sc = new Scanner(System.in);
      System.out.print("Enter the degree: ");
      int n = sc.nextInt();
      
      System.out.print("Enter "+(n+1)+" coefficients: ");  
      n = n+1;
      double[] C = new double[n];
      for(int i = 0; i < C.length; i++){
          C[i] = sc.nextDouble();
      } 
       
      System.out.print("Enter the left and right endpoints: ");
      double a = sc.nextInt();
      double b = sc.nextInt();

      sumA = poly(C, a);
      sumB = poly(C, b);

   static double poly(double[] C, double x){
      double sum = 0;
      for(int i=0; i<C.length; i++){
         for(int n; n>1; n--){
            sum += C[i]* Math.pow(x,n);
         }
      }
      return sum;
   }

      double esp = 0.00001; 
      double root = 0.0, residual;
      while (b - a > esp) {
         root = (a + b) / 2.0;
         residual = f(root);
         if(residual > 0) 
            b = root;
         else
            a = root;
      }
      System.out.print("root is " );
      System.out.printf("%.5f%n", root);

      printArray(C);

   }
   static void printArray(double[] C){
      System.out.print("Your array is (");
      for(int i=0; i<C.length; i++)
         System.out.print(C[i]+" ");
      System.out.println(")");
   }
   static double f(double x) { return (x*x-2.0);}
}
