//Seongwoo Choi
//scho29
//CMPS12B/M
//Programming Assignment 3
// The goal of this project is to implement a Dictionary ADT based on the linked  list  data structure.  

public class Dictionary implements DictionaryInterface{
  //This is inner class Node.
  //Pre: It takes a string value and a string key
  //Pos: and creates a structure for a linked list. 
  private class Node{
    String key;
    String value;
    Node next;
    //node class constructor
    Node(String key, String value){
      this.key = key;
      this.value = value;
      next = null;
    }
  }
  //private field. This controls the linked list ADT.
  private Node front;
  private int numItems;

  //the dictionary constructor initializes the private field
  public Dictionary(){
    front = null;
    numItems = 0;
  }
  //isEmpty
  //there is no pre.
  //Pos: returns true or false.
  public boolean isEmpty(){
    return (numItems==0);
  }
  //size 
  //Pre:none
  //pos:return the number of items inside the linked list.
  public int size(){
    return numItems;
  }
  //lookup 
  //Pre:takes a string 'key'
  //pos: return the value associated with the key or returns 
  //null if 'key' is not inside the list.
  public String lookup(String key){
    Node N = front;
    while( N != null){
      if( N.key.equals(key)){
        return N.value;
      }
      N = N.next;
    }
    return null;
  }
  //insert
  //Pre:this takes in two strings; a 'key' and 'value' which 
  //are not already in the linked list.
  //Pos:Adds 'key' and 'value' into the linked list or throws 
  //proper exception.
  //
  public void insert(String key, String value) throws KeyCollisionException{
    if( lookup(key) != null){
      throw new KeyCollisionException("cannot insert dublicate key");
    }
    else{
      if( front == null){
        Node N = new Node(key,value);
        front = N;
        numItems++;
      }
      else{
        Node N = front;
        while( N != null){
          if(N.next == null){
            break;
          }
          N = N.next;
        }
        N.next = new Node(key,value);
        numItems++;
      }
    }
  }

  //Pre: takes in the string 'key' which is in the list.
  //Pos: removes the 'key' as well as 'value' from the list. 
  public void delete(String key) throws KeyNotFoundException{
    if( lookup(key) == null){
      throw new KeyNotFoundException("cannot delete non-existent key");
    }
    else{
      if(numItems <= 1){
        Node N = front;
        front = front.next;
        N.next = null;
        numItems--;
      }
      else{
        Node N = front;
        if(N.key.equals(key)){
          front = N.next;
          numItems--;
        }
        else{
          while(!N.next.key.equals(key)){
            N = N.next;
          }
          N.next = N.next.next;
          numItems--;
        }
      }
    }
  }

  //makeEmpty
  //Pre: none
  //pos: makes the linked list
  public void makeEmpty(){
    front = null;
    numItems =0;
  }

  //toString
  //Pre: none
  //Pos: allows the user to print out the contenst of the linked list
  public String toString(){
    String s = "";
    Node N = front;
    while( N != null){
      s += N.key + " " + N.value + "\n"; 
      N = N.next;
    }
    return s;
  }

  //findKey
  //Pre: a string 'key'
  //Pos: returns the reference to where the 'key'is, or
  //returns null if there is no 'key' in the list
  private Node findKey(String key){
    Node N = front;
    while(N != null){
      if(N.key.equals(key)){
        return N; 
      }
      else{
        N = N.next; 
      }
    }
    return null;
  }
} 
