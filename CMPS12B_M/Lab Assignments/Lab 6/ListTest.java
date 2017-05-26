//Seongwoo Choi
//scho29
//CMPS12B/M
//LAboratory Assignment 6
//ListTest.java
public class ListTest {
    public static void main(String[] args) {
        List<String> A = new List<String>();
        List<String> B = new List<String>();
        List<List<String>> C = new List<List<String>>();

        int i, j, k;

        A.add(1, "one");
        A.add(2, "two");
        A.add(3, "three");
        System.out.println(A.isEmpty());
        System.out.println("A: " + A);
        System.out.println(A.size());
        System.out.println("A.get(2) is "+A.get(2));
        A.removeAll();
        System.out.println(A.isEmpty());
    }
}