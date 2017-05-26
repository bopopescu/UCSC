//Seongwoo Choi
//scho29
//CMPS12B/M
//Laboratory Assignment 6
//List.java

public class List<T> implements ListInterface<T> {
    //fields
    private static final int INITIAL_SIZE = 1;
    private int physicalSize;   //current length of underlying array
    private Object item[]; 
    private int numItems; //this is a number of items in the list. 

    //List
    //constructor for the List class
    public List() {
        physicalSize = INITIAL_SIZE;
        item = new Object[INITIAL_SIZE];
        numItems = 0;
    }

    //arrayIndex()
    //this section transforms a list index to an array index
    private int arrayIndex (int listIndex) {
        return listIndex - 1;
    }

    // doubleItemArray()
    // doubles the physical size of the underlying array item[]
    private void doubleItemArray() {
        physicalSize *= 2;
        Object[] newArray = new Object[physicalSize];
        for (int i = 0; i < numItems; i++) newArray[i] = item[i];
        item = newArray;
    }


    // isEmpty
    // pre: none
    // post:it returns true if this List is empty, false otherwise
    public boolean isEmpty() {
        return (numItems == 0);
    }

    // size
    // pre: none
    // post:it returns the number of elements in this List
    public int size() {
        return numItems;
    }

    // get
    // pre: 1 <= index <= size()
    // post: it returns item at position index
    @SuppressWarnings("unchecked")
    public T get(int index) throws ListIndexOutOfBoundsException {
        if (index >= 1 && index <= (numItems + 1)) {
            return (T) item[arrayIndex(index)];
        } else {
            throw new ListIndexOutOfBoundsException (
                "List error: called get() on an invalid index.");
        }
    }

    // add
    // inserts newItem in this List at position index
    // pre: 1 <= index <= size()+1
    // post: !isEmpty(), items to the right of newItem are renumbered
    public void add(int index, T newItem) throws ListIndexOutOfBoundsException {
        if (index < 1 || index > (numItems + 1)) { //way out of bounds
            throw new ListIndexOutOfBoundsException (
                "List Error: add() called on invalid index ");
        }

        if (numItems == physicalSize) {
            doubleItemArray();
        }
        for (int i = numItems; i >= index; i--) {           //makes room for new item
            item[arrayIndex(i + 1)] = item[arrayIndex(i)];  //shifts all items at i >= index
        }                                                   // towards the end of the list (no shift if index == numItems)
        item[arrayIndex(index)] = newItem;
        numItems++;
    }
   
    // remove
    // deletes item from position index
    // pre: 1 <= index <= size()
    // post: items to the right of deleted item are renumbered
    public void remove(int index) throws ListIndexOutOfBoundsException {
        if (index >= 1 && index <= numItems) {
            for (int post = index + 1; post <= numItems; post++) {
                item[arrayIndex(post - 1)] = item[arrayIndex(post)]; //delete given items by shifting all items at post > index
            }                                                        //towards the beginning of the list (no shift if index == numItems)
            numItems--;
        } else { //index is out of range
            throw new ListIndexOutOfBoundsException (
                "List Error: remove() called on invalid index ");
        }
    }

    // removeAll
    // pre: none
    // post: isEmpty()
    public void removeAll() {
        item = new Object[INITIAL_SIZE]; //dumps the whole array of numbers and lets java play cleanup
        numItems = 0;
    }


    // toString()
    // pre: none
    // post:  prints current state to stdout
    // Overrides Object's toString() method
    public String toString() {
        int i;
        String s = "";

        for (i = 0; i < numItems; i++) s += item[i] + " ";
        return s;
    }
}