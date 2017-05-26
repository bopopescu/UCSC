//Seongwoo Choi
//scho29
//CMPS 12B/M
//Programming assignment 3
//This progrma tests the function of Dictionary ADT 
//to make sure that the Dictionary ADT is functioning.


class DictionaryTest{
  public static void main (String[] args){
    Dictionary A = new Dictionary();
    System.out.println(A.isEmpty());
    A.insert("4","f");
    System.out.println(A.isEmpty());
    A.insert("5","d");
    System.out.println(A.size());
    A.insert("6","3");
    A.insert("7","c");
    A.insert("3","e");
    A.insert("9","3");

    System.out.println(A);
    System.out.println(A.lookup("7"));
    System.out.println("********");
    A.delete("6");
    System.out.println(A.size());
    System.out.println(A.lookup("6"));
    A.delete("5");
    A.delete("4");
    System.out.println(A.lookup("9"));
    System.out.println(A.size());
    System.out.println(A);
    A.makeEmpty();
    System.out.println(A.size() + " " + A.isEmpty());
    
  }
}