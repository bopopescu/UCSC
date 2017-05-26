//Seongwoo Choi
//scho29
//CMPS 101: Intro to Algorithms
//Patrick Tantalo
//Programming Assignment 1
//Comments are from the PDF Prof. Tantalo provided for students to copy and type on the assignment.

class List {
//Private Node Class:
	private class Node {
		int data;
		Node previous;
		Node next;
		Node (int data) {
			this.data = data;
			previous = null;
			next = null;
		}
		public String toString () {
			return (String.valueOf(data));
		}
	}
//Privata List Fields are here:
	private Node front;
	private Node back;
	private Node cursor;
	private int cursorIndex;
	private int length;

//Creates a new empy list. 
	List () {
		front = null;
		back = null;
		cursor = null;
		cursorIndex = -1;
		length = 0;
	}
//Returns the number of elements in the List.
	int length () {
		return length;
	}
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
	int getIndex () {
		return cursorIndex;
	}
//Returns front element in the list. Pre: length() >0
	int front () {
		if (length() != 0) {
			return front.data;
		} else {
			throw new RuntimeException("Error: front() " + 
				"called on an empty list.");
		}
	}
//Returns back element in the list. Pre: length()>0
	int back () {
		if (length() != 0) {
			return back.data;
		} else {
			throw new RuntimeException("Error: back() " +
				"called on an empty list.");
		}
	}
//Returns cursor element. Pre: length()>=0, getIndex()>=
	int getElement () {
		if (length() == 0) {
			throw new RuntimeException("Error: getElement() " +
				"called on an empty list.");
		} else if (getIndex() == -1) {
			throw new RuntimeException("Error: Cursor undefined.");
		} else {
			return cursor.data;
		}
	}
 // Returns true if this List and L are the same integer
 // sequence. The cursor is ignored in both lists.
	boolean equals (List L) {
		if (this.length == L.length) {
			Node temp1 = this.front;
			Node temp2 = L.front;
			while (temp1.next != null && temp2.next != null) {
				if (temp1.data == temp2.data) {
					temp1 = temp1.next;
					temp2 = temp2.next;
				} else return false;
			} return true;
		} else {
			return false;
		}
	}

//Manipulative Procedures
//Resets this List to its original empty state.	
	void clear () {
		for (Node N=front; N!=null; N=N.next) {
			Node temp = N;
			temp = null;
		}
		length = 0;
		cursor = null;
		front = null;
		back = null;
		cursorIndex = -1;
	}
//**If 0<=i<=length()-1, moves the cursor to the element
// at index i, otherwise the cursor becomes undefined.
	void moveTo (int i) {
		if (i >= length() || i < 0) {
			cursor = null;
			cursorIndex = -1;
		} else {
			cursor = front;
			cursorIndex = 0;
			for (int j = 0; j < i; j++) {
				moveNext();
			}
		}
	}
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
	void movePrev () {
		if (getIndex() <= 0) {
			cursorIndex = -1;
			cursor = null;
		} else if (0 < getIndex() && getIndex() < length()) {
			cursorIndex--;
			cursor = cursor.previous;
		}
	}
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing. 
	void moveNext () {
		if (getIndex() == -1 ) {
			cursor = front;
			cursorIndex = 0;
		} else if (getIndex() >= length()-1) {
			cursorIndex = -1;
			cursor = null;
		} else {
			cursor = cursor.next;
			cursorIndex++;
		}
	}
//Inserts data to the end of the list.
//If List is non-empty,
// insertion takes place after back element.
	void append (int data) {
		Node newNode = new Node (data);
		if (length == 0) {
			newNode.previous = null;
			newNode.next = null;
			front = newNode;
			back = newNode;
		} else {
			newNode.previous = back;
			newNode.next = null;
			back.next = newNode;
			back = newNode;
		}
		length++;
	}
//Inserts data to the front of the List.
// If List is non-empty,
// insertion takes place before front element.
	void prepend (int data) {
		Node newNode = new Node (data);
		if (length == 0) {
			newNode.previous = null;
			newNode.next = null;
			front = newNode;
			back = newNode;
		} else {
			newNode.previous = null;
			newNode.next = front;
			front.previous = newNode;
			front = newNode;
		}
		length++;
		//If defined, increment the cursor
		if (getIndex() != -1) {
			cursorIndex++;
			cursor = cursor.next;
		}
	}


//Inserts new element before the cursor
// Pre: length()>0, index()>=0
	void insertBefore (int data) {
		if (length() <= 0) {
			throw new RuntimeException ("Error: insertBefore() " + 
				"called on an Empty List.");
		} else if (getIndex() < 0) {
			throw new RuntimeException ("Error: Cursor Undefined");
		}
		Node newNode = new Node (data);
		if (getIndex() == 0) {
			prepend(data);
		} else {
			newNode.next = cursor;
			newNode.previous = cursor.previous;
			cursor.previous.next = newNode;
			cursor.previous = newNode;
			cursorIndex++;
			length++;
		}
	}
//Inserts new element after the cursor.
// Pre: length()>0, index()>=0
	void insertAfter (int data) {
		if (length() <= 0) {
			throw new RuntimeException ("Error: Empty List.");
		} else if (getIndex() < 0) {
			throw new RuntimeException ("Error: Cursor Undefined.");
		}
		Node newNode = new Node (data);
		if (getIndex() == length()-1) {
			append(data);
		} else {
			newNode.next  = cursor.next;
			newNode.previous = cursor;
			cursor.next = newNode;
			cursorIndex++;
			length++;
		}
		
	}

	//**Removes the back element of the list
	// Pre: length()>0
	void deleteBack () {
		Node temp = back;
		if (cursor == back) {
			cursor = null;
			cursorIndex = -1;
		}
		back.previous.next = null;
		back.previous = back;
		temp = null;
	}
	//**removes the front element of the list
	// Pre: length()>0

	void deleteFront () {
		Node temp = front;
		if (cursor == front) {
			cursor = cursor.next;
		}
		front.next.previous = null;
		front.next = front;
		temp = null;
	}
	//Deletes the cursor element of the List.
	// Pre: length()>0, index()>=0
	void delete () {
		if (getIndex() == -1) {
			throw new RuntimeException ("Error: delete()" +
				"called on list with an undefined cursor.");
		}
		Node temp = cursor;
		if (cursor == back) {
			deleteBack();
		} else if (cursor == front) {
			deleteFront();
		}
		cursor.previous.next = cursor.next;
		cursor.next.previous = cursor.previous;
		cursor = cursor.previous;
		temp = null;
	}
 // Returns a new List representing the same integer sequence as this
 // List. The cursor in the new list is undefined, regardless of the
 // state of the cursor in this List. This List is unchanged.
	List copy () {
		List L = new List();
		for (Node n = this.front; n!=null; n=n.next) {
			L.append(n.data);
		}
		return L;
	}
 // Overrides Object's toString method. Returns a String
 // representation of this List consisting of a space
 // separated sequence of integers, with front on left.
	public String toString () {
		String str = "";
    	for(Node N=front; N!=null; N=N.next){
    		str += N.toString() + " ";
      	}
    	return str;
	}

}
