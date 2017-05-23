///////////////////////////////////////////////////////////////////////////////
//  
//  Queens.java
//  Seongwoo Choi
//  scho29
//  pa5
//  prints solutions and/or permutations to n Queens
//
//////////////////////////////////////////////////////////////////////////////

class Queens{

   public static void main(String[] args){
   
      boolean verbosemode = false; 
      boolean solution = false;
      int argNum=1;
      if(args.length == 2){
         try{
            argNum = Integer.parseInt(args[1]); 
         }catch(Exception e){
            System.out.println("Usage: Queens [-v] number");
            System.out.println("Option: -v verbose output, print all solutions");
            System.exit(1);
         } 
         verbosemode = true;
      }
      if(args.length == 1){
         try{
            argNum = Integer.parseInt(args[0]); 
         }catch(Exception e){
            System.out.println("Usage: Queens [-v] number");
            System.out.println("Option: -v verbose output, print all solutions");
            System.exit(1);
      }   
         }if(args.length == 0 || args.length >= 3){
            System.out.println("Usage: Queens [-v] number");
            System.out.println("Option: -v verbose output, print all solutions");
            System.exit(1);
         } 

         int[] array = new int[argNum+1];
         int count = 0;
         for(int i=1;i<array.length;i++){
            array[i]=i; 
         }
         for(int i=1; i<factorial(argNum); i++){
            if(isSolution(array)){
               if(verbosemode == true){
               arrayPrint(array);
               }
               count++;
            }
          array = nextPermutation(array).clone(); 

         }
      System.out.println(argNum+"-Queens has "+count+" solutions");
   }

   static int[] nextPermutation(int[] A){
      int successPoint = 0;
      int pivotPoint = 0;
      int a, b, c, d;
      for(a = A.length - 1; a > 1; a--){
         if(A[a - 1] < A[a]){
            pivotPoint = a - 1;
            break ;
         }
      }
      if(a == 0){
         reverse(A, 1, A.length - 1);
      }
      for(a = A.length - 1; a >= 1; a--){
         if(A[a] > A[pivotPoint]){
            successPoint = a;
            break;
         }
      }
      swap(A, pivotPoint, successPoint);
                
      reverse(A, pivotPoint+1, A.length - 1);
      return A;
   }

   static boolean isSolution(int[]A){
      int a = 2;
      for(int i = 1; i <= A.length - 1; i++){
         for(int b = a; b <= A.length - 1; b++){
            if(Math.abs(A[i] - A[b]) == Math.abs(i - b)){
               return false;
            }
         }
         a++;
      }
         return true;
   }

   static void swap(int[] E, int i, int j){
      int temp = E[i];
      E[i] = E[j];
      E[j] = temp;
   } 
   static void reverse(int[] F, int i, int k){
      while(i<k){
         swap(F,i,k);
         i++;
         k--;
      }
   }
   static int factorial(int i){
      int product = 1;
      for(int a = i; a > 1; a--){
      product *= a;
      }
      return product;
   }
   static void arrayPrint(int[] P){
      System.out.print("(");
      for(int i=1; i<P.length; i++){
         System.out.print(P[i]+", ");
      }
      System.out.print(P[P.length-1]+ ")");
      System.out.println();
   }   
}
