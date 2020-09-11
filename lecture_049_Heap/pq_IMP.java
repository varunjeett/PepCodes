import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Vector;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.Scanner;

//priority queue in java : add
public class pq_IMP {

    public static class student /*implements Comparable<student> (for method 2)*/{
        int roll;
        String name;
        int marks;

        student(int roll_, String name_, int marks_) {
            this.roll=roll_;    this.name=name_;    this.marks=marks_;
        }

        @Override
        public String toString() {
            String str=this.roll+","+this.name+","+this.marks;
            return str;
        }

        //method 2 : comparable
        // @Override
        // public int compareTo(student o) {
             // return this.roll - o.roll; //ascending roll no
               // return o.marks - this.marks; //descending marks
        //     return o.name.compareTo(this.name); //by name.
        // }

    }

    //method 3: using Comparator 
    public static class myComparator implements Comparator<student> {
        
        @Override
        public int compare(student s1, student s2) 
        { 
            // return s1.roll - s2.roll; //ascending roll no
            return s2.marks - s1.marks; //descending marks
            // return s1.name.compareTo(s2.name); //by name.
        } 
    }

    public static void main(String[] args) {

        // PQ_FOR_INTEGER();
        PQ_FOR_CLASS_OBJ();
    }

    public static void PQ_FOR_INTEGER() {
        int[] arr = { 1034, 34, 56, 2,12323,4,121212, 454, 2, -1, -100 };
        PriorityQueue<Integer> pq = new PriorityQueue<>(); //=========min heap

        // PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());  //============max heap

        // PriorityQueue<Integer> pq = new PriorityQueue<Integer>(new Comparator<Integer>() {   //=======max heap
        //     @Override
        //     public int compare(Integer a, Integer b) {
        //         return b - a;
        //     }
        // });

        // PriorityQueue<Integer> pq = new PriorityQueue<Integer>( (Integer a, Integer b) -> b - a); //max heap

        for (int ele : arr)
            pq.add(ele);

        while (pq.size() != 0) {
            System.out.println(pq.poll());
        }
    }

    public static void PQ_FOR_CLASS_OBJ() {

        Scanner scn=new Scanner(System.in);
        ArrayList<student> arr=new ArrayList<>();
        for(int i=0; i<5; i++) {
            int a=scn.nextInt();
            String b=scn.next();
            int c=scn.nextInt();
            arr.add(new student(a, b, c));
        }
    

        // for(student s:arr) {
        //     System.out.println(s);
        // }

        //method 1 : by using lambda function
        // PriorityQueue<student> pq=new PriorityQueue<student>((student s1, student s2)->{
            // return s2.roll-s1.roll;          //descending rollno.
            // return s1.marks - s2.marks;      //ascending marks.
        //     return s1.name.compareTo(s2.name);  //lexographical
        // });

        //  method 2: using comparable.
        // PriorityQueue<student> pq=new PriorityQueue<student>();

        //method 3: using comparator class
        PriorityQueue<student> pq=new PriorityQueue<student>(new myComparator());

        for(student s:arr) {
            pq.add(s);
        }

        while(pq.size()!=0) {
            System.out.println(pq.poll());
        }
    }

}