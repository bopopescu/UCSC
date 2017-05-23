class Test{

   public static void main(String args[]){
      int[] A = {0,1,2,3};
      boolean solution;
      solution = isSolution(A); 
      System.out.println(solution);
  } 

   static boolean isSolution(int[] B){
      boolean solution = false;
      int i=1;
      //int count = B[0]; 
      for(int j=2;j<B.length;j++){
         int s = Math.abs(B[i] - B[j]);
         System.out.println(s);
         int n = Math.abs(i - j);
         System.out.println(n);
         if(s==n){
            //count++;
            solution = false;
            break;
         }
         else solution = true;
      
         if(j==B.length-1){
            i++;
            j=i+1; 
         }
      }
         return solution; 
   }
}
