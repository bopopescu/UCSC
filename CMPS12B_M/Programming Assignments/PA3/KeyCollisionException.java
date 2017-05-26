//Seongwoo Choi
//scho29
//CMPS12B/M
//Programming Assignment 3
//This throws any exception if there are duplicate files inserted into the linked list. 

public class KeyCollisionException extends RuntimeException{
  public KeyCollisionException( String s){
    super(s);
  }
}