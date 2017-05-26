//-----------------------------------------------------------------------------
// Seongwoo Choi
// scho29
// CMPS12B/M
// Programming Assignment 2
//-----------------------------------------------------------------------------

// FileReverse.java
// Illustrates file IO and tokenization of strings.
import java.io.*;
import java.util.Scanner;

public class Search {
   public static void main(String[] args) throws IOException{
      
      Scanner fileInput = null;
      String line = null;
      String[] token = null;
      int numOfLines = 0;
      int[] lineNumber = null;
      
      // check command line arguments
      if(args.length < 2){
         System.out.println("Usage: Search infile outfile");
         System.exit(1);
      }

      fileInput = new Scanner(new File(args[0]));


      // read lines from in, extract and print tokens from each line 
      while( fileInput.hasNextLine() ){
      	numOfLines++;
         line = fileInput.nextLine();
    }
    token = new String[numOfLines];
    lineNumber = new int[numOfLines];
    fileInput = new Scanner(new File(args[0]));
 
      for (int i=1; i<=lineNumber.length; i++){
         lineNumber[i-1] = i;
      }

      for(int i = 0; fileInput.hasNextLine(); i++){
      	line = fileInput.nextLine();
      	token[i] = line;
      }
   	mergeSort(token, lineNumber, 0, token.length-1);
   	for(int i=1; i<args.length; i++){
   		System.out.println( binarySearch(token, lineNumber, 0, token.length-1, args[i]));
   	}


   	fileInput.close();
   } 



   // mergeSort()
   // sort subarray A[p...r]
   public static void mergeSort(String[] word, int[] lineNumber, int p, int r){
      int q;
      if(p < r) {
         q = (p+r)/2;
         // System.out.println(p+" "+q+" "+r);
         mergeSort(word, lineNumber, p, q);
         mergeSort(word, lineNumber, q+1, r);
         merge(word, lineNumber, p, q, r);
      }
   }

   // merge()
   // merges sorted subarrays A[p..q] and A[q+1..r]
   public static void merge(String[] word, int[] lineNumber, int p, int q, int r){
      int n1 = q-p+1;
      int n2 = r-q;
      String[] left = new String[n1];
      String[] right = new String[n2];
      int[] L = new int[n1];
      int[] R = new int[n2];
      int i, j, k;

      for(i=0; i<n1; i++) {
      	left[i] = word[p+i];
      	L[i] = lineNumber[p+i];
      }

      	
      for(j=0; j<n2; j++) {
      	right[j] = word[q+j+1];
      	R[j] = lineNumber[q+j+1];
      }
      
      i = 0; j = 0;
      for(k=p; k<=r; k++){
         if( i<n1 && j<n2 ){
            if( left[i].compareTo(right[j]) > 0 ){
               word[k] = left[i];
               lineNumber[k] = L[i];
               i++;
            }else{
               word[k] = right[j];
               lineNumber[k] = R[j];
               j++;
            }
         }else if( i < n1 ){
            word[k] = left[i];
            lineNumber[k] =L[i];
            i++;
         }else{ // j<n2

            word[k] = right[j];
            lineNumber[k] = R[j];
            j++;
         }
      }
   }

   // binarySearch()
   // pre: Array A[p..r] is sorted
   public static String binarySearch(String[] word, int[] lineNumber, int p, int r,  String target){
      int q;
      if(p == r) {
         return target + " not found";
      }else{
         q = (p+r)/2;
         if(word[q].compareTo(target) == 0){
            return target + " found on line " + lineNumber[q];
         }else if(word[q].compareTo(target) < 0){
            return binarySearch(word, lineNumber, p, q, target);
         }else{ // target > A[q]
            return binarySearch(word, lineNumber, q+1, r, target);
         }
      }
   }
}

