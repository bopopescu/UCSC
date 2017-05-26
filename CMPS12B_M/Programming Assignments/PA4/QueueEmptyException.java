/*Exception class
//Seongwoo Choi
//scho29
//CMPS12B/M
//Programming Assignment 4
 *Throws an Error
 */ 
public class QueueEmptyException extends RuntimeException{
   public QueueEmptyException(String s){
      super(s);
   }
}