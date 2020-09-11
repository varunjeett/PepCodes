import java.util.Scanner;

public class L001 {

    public static Scanner scn = new Scanner(System.in);

    public static void main(String[] args) {

        solve();

    }

    public static void solve() {

        // set1();
        set2();

    }

    public static void set1() {

        int a, b;
        a = scn.nextInt();
        b = scn.nextInt();

        int res = powerPrint(a, b);
        int res2 = Factorial(a);
        int res3 = powerBTR(a, b);

        System.out.println(res);

        System.out.println(res2);

        System.out.println(res3);

    }

    public static int powerPrint(int a, int b) {

        if (b == 0) {

            return 1;

        }

        int smallAns = powerPrint(a, b - 1);
        return smallAns * a;

    }

    public static int Factorial(int a) {

        if (a <= 1) {

            return 1;
        }

        int smallAns = Factorial(a - 1);
        return smallAns * a;
    }

    public static int power(int a, int b) {

        if (b == 0) {

            return 1;

        }

        int smallAns = power(a, b - 1);
        return smallAns * a;

    }

    public static int powerBTR(int a, int b) {

        if (b == 0) {

            return 1;

        }

        int smallAns = powerBTR(a, b / 2); // time complexity log base 2 mein jaake bhut improve hgyi
        smallAns *= smallAns;

        return (b % 2 == 0) ? smallAns : smallAns * a;

    }

    // set 1 ends here

    public static void display(int[] arr, int s_index) {

        if (s_index == arr.length) {
            return;
        }

        System.out.println(arr[s_index]);
        display(arr, s_index + 1);

    }

    public static int maximum(int[] arr, int s_index) {
        if (s_index == arr.length - 1) {
            return arr[s_index];
        }

        return Math.max(arr[s_index], maximum(arr, (s_index + 1))); // work is in post area

    }

    public static int minimum(int[] arr, int s_index) {
        if (s_index == arr.length - 1) {
            return arr[s_index];
        }

        return Math.min(arr[s_index], minimum(arr, (s_index + 1)));

    }

    static int curr_max = -1;

    public static void maximum_02(int[] arr, int s_index) {

        if (s_index == arr.length) {
            return;
        }

        curr_max = Math.max(arr[s_index], curr_max);
        maximum_02(arr, (s_index + 1));

    }

    public static void find_01(int[] arr, int data, int s_index) {

        if (s_index == arr.length) {
            System.out.println("not found"); // base case
            return;
        }

        if (arr[s_index] == data) {
            System.out.println("found at " + (s_index + 1) + "th position"); // base case
        }

        find_01(arr, data, s_index + 1); // work in pre area
        
        return;
    }

    public static void find_02(int[] arr, int data, int s_index) {

        if (s_index == arr.length) {

            return;

        }
        find_02(arr, data, (s_index + 1));

        // work in post area
        if (arr[s_index] == data) {
            System.out.println("found at " + (s_index + 1) + "th postion");
        }

    }

    public static void set2() { // recursion with array

        int i;
        int len = scn.nextInt();
        int[] arr = new int[len];

        for (i = 0; i < arr.length; i++) {

            arr[i] = scn.nextInt();

        }

        display(arr, 0);
        // int res=maximum(arr,0);
        // System.out.println("max element "+ res);

        // int res2=minimum(arr,0);
        // System.out.println("min element "+ res2);

        // maximum_02(arr,0);
        // System.out.println("max element also " + curr_max);

        int data = scn.nextInt();
        find_02(arr, data, 0);

    }

}
