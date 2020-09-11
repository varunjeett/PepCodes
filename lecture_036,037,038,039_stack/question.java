//sliding window max subarray 
class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int n = nums.length;
        if (n == 1 || k == 1)
            return nums;

        int[] ans = new int[n - k + 1]; // total possible number of windows.
        int max_ = -100000;

        int idx = 0;

        for (int i = 0; i < k; i++) {
            max_ = Math.max(max_, nums[i]); // max for first window
        }

        ans[idx++] = max_;

        int start = 0; // last element of the previous window
        for (int i = k; i < n; i++) {

            if (nums[start] == max_) { // as the element at start is removed from the window(similiar to DQ)
                max_ = nums[start + 1]; // taking max for the whole window now as old max is lost
                for (int pos = start + 2; pos <= i; pos++) {
                    max_ = Math.max(max_, nums[pos]);
                }
            }

            else {
                max_ = Math.max(max_, nums[i]); // old max not lost , so check with the incoming value
            }

            start++;
            ans[idx++] = max_;
        }

        return ans;

    }
}

// for 140 , 100, 80, 60, 110, 120

// now for 110 the span will be of 4, now since 120 is greater than 110 so the
// span of 120 will be ATLEAST (SPAN OF 110) +1

// THATS WHY , WE DONT NEED TO RESTORE THESE COMMON ELEMENTS, AS INDEX WILL HELP
// US.

class StockSpanner {
    Stack<int[]> st;
    int i;

    public StockSpanner() {
        st = new Stack<>();
        st.push(new int[] { -1, -1 });
        i = 0;
    }

    public int next(int price) {
        int[] obj = new int[] { price, i++ };
        while (st.peek()[1] != -1 && st.peek()[0] <= obj[0]) {
            st.pop();
        }
        int ans = obj[1] - st.peek()[1];
        st.push(obj);
        return ans;

    }
}
