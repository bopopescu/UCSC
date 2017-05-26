//-----------------------------------------------------------------------------
// Extrema.java
// Seongwoo Choi
// scho29
// pa1
// uses recursion to find the maximum and minimum integer in a given array
//-----------------------------------------------------------------------------

class Extrema {
   
   // maxArray()
   // returns the largest value in int array A
   static int maxArray(int[] A, int p, int r){
		int q;
		if(p == r){
			return A[p];
		} else {
			q = (p + r) /2;
			return max(maxArray(A, p, q), maxArray(A, q + 1, r));
		}
   }
   
   // minArray()
   // returns the smallest value in int array A
   static int minArray(int[] A, int p, int r){
		int q;
		if(p == r){
			return A[p];
		} else {
			q = (p + r) /2;
			return min(minArray(A, p, q), minArray(A, q + 1, r));
		}
   }
   
   // max()
   // a helper function that returns the maximum of a pair of ints
   static int max(int num1, int num2){
     return (num1 > num2 ? num1:num2);
   }
   
   // min()
   // a helper function that returns the minimum of a pair of ints
   static int min(int num1, int num2){
	 return (num1 < num2 ? num1:num2);
   }
   
   // main()
   public static void main(String[] args){
      int[] B = {-1, 2, 6, 3, 9, 2, -3, -2, 11, 5, 7};
      System.out.println( "max = " + maxArray(B, 0, B.length-1) );  // output: max = 11
      System.out.println( "min = " + minArray(B, 0, B.length-1) );  // output: min = -3
   }
}