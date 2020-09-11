import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

// IN AL, WE HAVE add() AND remove(index) FUNCTIONS , get(idx) and set(idx,value)

public class L048 {
    // heap class
    public static class myHeap {
        private ArrayList<Integer> arr = new ArrayList<>();
        private boolean isMaxheap = true; // by default we have taken max heap

        myHeap(int[] val, boolean isMax) {

            this.isMaxheap = isMax;
            for (int ele : val) {
                this.arr.add(ele);
            }

            for (int i = val.length; i >= 0; i--) {
                this.downHeapify(i);
            }
        }

        private boolean compareTo(int child, int par) {
            if (isMaxheap)
                return this.arr.get(child) > this.arr.get(par); // RETURN TRUE AS WE NEED TO UPDATE THE PARENT IN THE
                                                                // CALLER FN
            else
                return this.arr.get(child) < this.arr.get(par);
        }

        private void swap(int idx1, int idx2) {
            int a = this.arr.get(idx1);
            int b = this.arr.get(idx2);

            this.arr.set(idx1, b);
            this.arr.set(idx2, a);
        }

        private void downHeapify(int idx) {
            int pi = idx;

            int lChild = 2 * pi + 1;
            int rChild = 2 * pi + 2;

            if (lChild < this.arr.size() && compareTo(lChild, pi))
                pi = lChild;
            if (rChild < this.arr.size() && compareTo(rChild, pi))
                pi = rChild;

            // if (pi == idx) // no need to do anything BASE CASE

            if (pi != idx) {
                swap(idx, pi); // badi value ko parent bnadia aur uski jagah arr[idx] ne li
                this.downHeapify(pi);
            }

            return;
        }

        private void upHeapify(int child) {
            int par = (child - 1) / 2;

            if (par >= 0 && this.arr.get(par) < this.arr.get(child)) {
                swap(par, child);
                upHeapify(par);
            }
            return;
        }

        // public client
        // functions.==========================================================

        // to illustrate recursion in
        // Heap.===============================================================
        public void display(int idx) {
            if (idx >= this.arr.size())
                return;

            String str = "";

            str += 2 * idx + 1 < this.arr.size() ? this.arr.get(2 * idx + 1) : ".";
            str += "<- " + arr.get(idx) + " ->";
            str += 2 * idx + 2 < this.arr.size() ? this.arr.get(2 * idx + 2) : ".";

            System.out.println(str);

            // recursive call on the array
            display(2 * idx + 1);
            display(2 * idx + 2);
            return;
        }

        public int height(int idx) { // in terms of edges, thats why for a leaf height is 0.
            if (idx >= this.arr.size())
                return -1; // for a null left/right child,return -1

            int lHeight = height(2 * idx + 1);
            int rHeight = height(2 * idx + 2);

            return Math.max(lHeight, rHeight) + 1;
        }

        public boolean isEmpty() {
            return this.arr.size() == 0 ? true : false;
        }

        public int size() {
            return this.arr.size();
        }

        public int top() {
            if (this.arr.size() == 0)
                return -1;

            return arr.get(0);
        }

        public void add(int ele) {
            this.arr.add(ele); // PUSHING ELEMENT AT LAST.
            upHeapify(this.arr.size() - 1);
        }

        public void pop() {
            if (this.arr.size() == 0)
                return;

            swap(0, this.arr.size() - 1);
            arr.remove(this.arr.size() - 1);
            downHeapify(0);
        }
    }

    // for heapsort.=======================================================
    public static void swap_(int idx1, int idx2, ArrayList<Integer> arr) {
        int a = arr.get(idx1);
        int b = arr.get(idx2);

        arr.set(idx1, b);
        arr.set(idx2, a);
    }

    public static void downHeapify_(int idx, int limit, ArrayList<Integer> arr) {
        int maxIdx = idx;

        int lChild = 2 * maxIdx + 1;
        int rChild = 2 * maxIdx + 2;

        if (lChild <= limit && arr.get(lChild) > arr.get(maxIdx))
            maxIdx = lChild;
        if (rChild <= limit && arr.get(rChild) > arr.get(maxIdx))
            maxIdx = rChild;

        if (maxIdx != idx) {
            swap_(maxIdx, idx, arr); // badi value ko parent bnadia aur uski jagah arr[idx] ne li
            downHeapify_(maxIdx, limit, arr);
        }

        return;
    }

    public static void heapSort(ArrayList<Integer> arr) {

        int n = arr.size();
        for (int i = n - 1; i >= 0; i--) {
            downHeapify_(i, arr.size() - 1, arr);
        }

        System.out.println(arr);

        int j = n - 1;
        while (j > 0) {
            swap_(0, j, arr);
            //limit of downheapify is used here
            downHeapify_(0, j - 1, arr);
            j--;
        }

        System.out.println(arr);
    }

    public static void main(String[] args) {

        int[] arr = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };

        myHeap hp = new myHeap(arr, false);
        hp.display(0);

        while (hp.size() != 0) {
            System.out.print(hp.top() + ",");
            hp.pop();
        }

        hp.pop();
        hp.pop();
        hp.pop();
        hp.pop();
        hp.pop();
        while (hp.size() != 0) {
            System.out.print(hp.top() + ",");
            hp.pop();
        }

        // ArrayList<Integer> val = new ArrayList<Integer>(
        // Arrays.asList(10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13));
        // heapSort(val);
    }
}