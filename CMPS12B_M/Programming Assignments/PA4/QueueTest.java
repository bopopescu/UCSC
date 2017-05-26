/*Seongwoo Choi
//scho29
//CMPS12B/M
//Programming Assignment 4
 *Test the method and the Queue to see if the stack is functioning 
 *correctly  
 */ 

public class QueueTest {
    public static void main(String[] args) {
        Queue A = new Queue();

        A.enqueue(5); A.enqueue(3); A.enqueue(9); A.enqueue(7); A.enqueue(10);
        System.out.println(A);
        A.dequeue(); A.dequeue();
        System.out.println(A);
        System.out.println(A.length());
        System.out.println(A.peek());
        A.dequeue(); A.dequeue();
        System.out.println(A.peek());
    }
}