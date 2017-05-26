//Seongwoo Choi
//scho29
//CMPS12B/M
//Programming assignment 3
//This java file allows to throw an exception if the user attempts to delete an nonexistent key in the program

public class KeyNotFoundException extends RuntimeException{
  public KeyNotFoundException(String s){
    super(s);
  }
}