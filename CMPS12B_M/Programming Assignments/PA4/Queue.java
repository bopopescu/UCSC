/*Seongwoo Choi
 * Queue ADT Class
 *
 */
public class Queue implements QueueInterface {

    private class Node {
        Object item;
        Node next;

        Node(Object x) {
            item = x;
            next = null;
        }
    }
    private Node head;
    private Node tail;
    private int length;

    public Queue() { //use for keep track of the data in the queue
        head = null;
        tail = null;
        length = 0;
    }

    // isEmpty()
    // pre: none
    // post: returns true if this Queue is empty, false otherwise
    public boolean isEmpty() {
        return (length == 0);
    }

    // length()
    // pre: none
    // post: returns the length of this Queue.
    public int length() {
        return length;
    }


    // enqueue()
    // adds newItem to back of this Queue
    // pre: none
    // post: !isEmpty()
    public void enqueue(Object newItem) {
        if (isEmpty()) {
            Node N = new Node(newItem);
            N.next = head;
            head = N;
        } else {
            Node N = head;
            while (N.next != null) {
                N = N.next;
            }
            N.next = new Node (newItem);
        }
        length++;
    }

    // dequeue()
    // deletes and returns item from front of this Queue
    // pre: !isEmpty()
    // post: this Queue will have one fewer element
    public Object dequeue() throws QueueEmptyException {
        Node N;
        if (isEmpty()) {
            throw new QueueEmptyException(
                "cannot dequeue() at an empty queue my friend.");
        } else {
            N = head;
            head = head.next;
        }
        length--;
        return N.item;
    }


    // peek()
    // pre: !isEmpty()
    // post: returns item at front of Queue
    public Object peek() throws QueueEmptyException {
        if (isEmpty()) {
            throw new QueueEmptyException(
                "cannot peek() at an empty queue my friend.");
        } else {
            return head.item;
        }

    }
    // dequeueAll()
    // sets this Queue to the empty state
    // pre: !isEmpty()
    // post: isEmpty()
    public void dequeueAll() throws QueueEmptyException {
        head = null;
        tail = null;
        length = 0;
    }

    // toString()
    // overrides Object's toString() method
    public String toString() {
        String s = "";
        Node N = head;
        while (N != null) {
            s += N.item.toString() + " ";
            N = N.next;
        }
        return s;
    }
}