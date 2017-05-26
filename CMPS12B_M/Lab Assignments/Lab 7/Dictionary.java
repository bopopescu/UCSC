/* 
Seongwoo Choi
1368039
scho29
CMPS12B/M
Laboratory Assignment 7
*/

public class Dictionary implements DictionaryInterface{
  //inner private class which constructs the ADT 
  private class Node{
    String key;
    String value;
    Node left;
    Node right;
    //private class constructor
    Node(String key, String value){
      this.key = key;
      this.value = value;
      left = null;
      right = null;
    }
  }
  /*findkey
   *Pre: it takes Node N, and int key 
   *Pos: it returns the reference to N which holds the key, if none is found, findKey return null;
   */ 
  private Node findKey(Node R, String k){
    if ( R == null || k.equals(R.key)) {
      return R;
    }
    if((k.compareTo(R.key)) < 0) {
      return findKey(R.left,k);
    }
    else{
      return findKey(R.right,k);
    }
  }
  /*findParent
   *Pre: it takes two Node references  
   *Pos: this part returns the parent of the Nodes 
   */ 
  private Node findParent(Node N, Node R){
    Node P = null;
    if( N != R ){
      P = R;
      for(; P.left!=N && P.right!=N; P=((N.key.compareTo(P.key) < 0 )? P.left:P.right)){
      }
    }
    return P;
  }
  /*fineLeftMost
   *Pre: it takes a Node N 
   *Pos: it returns the reference to the left most leef/node  
   */ 
  private Node findLeftMost(Node N){
    Node L = N;
    if( L!= null){
      for(; L.left!=null; L = L.left){
      }
    }
    return L;
  }
  /*printInOrder
   *Pre:takes a Node N 
   *Pos:puts the keys in increasing numeric order into a string 
   */ 
  private String printInOrder(Node N){
    String s ="";
    if( N!=null){ 
      s = printInOrder(N.left) + N.key + " " + N.value + "\n" +printInOrder(N.right);
    }
    return s;
  }
  //private Node and int
  private Node root;
  private int numPairs;
 
  // Dictionary constructors
  Dictionary(){
    root = null;
    numPairs = 0;
  }
  /*isEmpty
   *Pre:none
   *Pos:returns true or false 
   */ 
  public boolean isEmpty(){
    return (numPairs == 0);
  }
  
  /*size
   *Pre: none
   *Pos: return the size of the ADT
   */
  public int size(){
    return numPairs;
  }
  /*lookup
   *Pre: there is no Pre... 
   *Pos:returns the value associated with int k(the key) or UNDEF 
   */ 
  public String lookup(String key){
    Node N = findKey(root,key);
    if (N!=null){
      return N.value;
    }
    else{
      return null;
    }
  }
  /*insert
   *Pre:int k must not already be in the ADT 
   *Pos: adds int k and v into the ADT 
   */
  public void insert(String key, String value) throws KeyCollisionException{
    Node N, A, B;
    if ( findKey(root,key) != null){
      throw new KeyCollisionException("Cannot insert() duplicate keys");
    }
    N = new Node(key,value);
    B = null;
    A = root;
    
    while( A != null){
      B = A;
      if((key.compareTo(A.key)) < 0){
        A = A.left;
      }
      else{
        A = A.right;
      }
    }
    if( B == null){
      root = N;
    }
    else if( (key.compareTo(B.key))< 0){
      B.left = N;
    }
    else{
      B.right = N;
    }
    numPairs++;
  }
  
  /*delete
   *Pre: int k should be in the dictionary ADT 
   *Pos: this part deletes the key and values associated with k from the ADT 
   */ 
  public void delete(String key) throws KeyNotFoundException{
    Node N, P, S;
    N = findKey(root,key);
    if( N == null){
      throw new KeyNotFoundException("Cannot delete() non-existant key");
    }
    if( N.left == null && N.right == null){
      if(N == root){
        root = null;
      }else{
        P = findParent(N,root);
        if ( P.right == N){
          P.right = null;
        }else{
          P.left = null;
        }
      } 
    }else if( N.right == null){
      if ( N == root){
        root = N.left; // sets null to N.left
      }else{
        P = findParent(N,root);
        if ( P.right == N){
          P.right = N.left;
        }
        else{
          P.left = N.left;
        }
      }
    }else if( N.left == null){
      if( N == root){
        root = N.right; // this allows null to set N.right
      }
      else{
        P = findParent(N,root);
        if(P.right == N){
          P.right = N.right;
        }
        else{
          P.left = N.right;
        }
      }
    }
    else{
      S = findLeftMost(N.right);
      N.key = S.key;
      N.value = S.value;
      P = findParent(S,N);
      if(P.right == S){
        P.right = S.right;
      }
      else{
        P.left = S.right;
      }
    }
    numPairs--;
  }
  /*makeEmpty
   *Pre: none 
   *Pos: this sets root to null and numPairs to zero. 
   */ 
  public void makeEmpty(){
    root = null;
    numPairs = 0;
  }
  /*toString
   *Pre:none 
   *Pos: this overides the Object toString method 
   */ 
  public String toString(){
    String s = printInOrder(root);
    return  s; 
  }
  
}