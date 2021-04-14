import java.util.ArrayList;
import java.util.Scanner;

public class L002 {
    
    
  public static void main(String[] args) {
    solve();
  }

  public static void solve() {
    set3_recursion();
  }

  public static void set3_recursion() {
    String str = "aba";

    // System.out.println(subseq_byreturn(str)); //direct bhi print kr skte hai,
    // vrna loop aur nayi list bhi lga skte hain

    // System.out.println( subseq_byvoid(str,"") );

    // System.out.println(permutate_withRepet_return(str));

    // System.out.println(permutate_withRepet_void(str,""));

    System.out.println(permutate_withoutRepet_onlyVoid(str, ""));
  }

  public static ArrayList<String> subseq_byreturn(String str) {
    if (str.length() == 0) {
      ArrayList<String> base = new ArrayList<>();
      base.add("");
      return base;
    }

    char ch = str.charAt(0);
    ArrayList<String> smallAns = subseq_byreturn(str.substring(1));

    ArrayList<String> myAns = new ArrayList<>();

    myAns.addAll(smallAns); // smallans ka content myans mein copy krdega like a copy constructor

    for (String s : smallAns) {
      myAns.add(ch + s);
      // myAns.add(s); line 48 ko off krke yh vali lga skte hain
    }

    return myAns;
  }

  public static int subseq_byvoid(String str, String ans) {
    if (str.length() == 0) {
      System.out.println(ans);
      return 1;
    }

    int count = 0;
    char ch = str.charAt(0);

    count += subseq_byvoid(str.substring(1), ans + ch); // phla element included
    count += subseq_byvoid(str.substring(1), ans); // phla element not included

    return count;
  }

  public static ArrayList<String> permutate_withRepet_return(String str) {
    if (str.length() == 1) {
      ArrayList<String> base = new ArrayList<>();
      base.add(str);
      return base;
    }

    char ch = str.charAt(0);

    ArrayList<String> smallAns = permutate_withRepet_return(str.substring(1));

    ArrayList<String> myAns = new ArrayList<>();

    for (String s : smallAns) {
      for (int i = 0; i <= s.length(); i++) {
        myAns.add(s.substring(0, i) + ch + s.substring(i));
      }
    }

    return myAns;
  }

  public static int permutate_withRepet_void(String str, String ans) {
    if (str.length() == 0) {
      System.out.println(ans);
      return 1;
    }

    int count = 0;

    // approach 1

    // char ch=str.charAt(0);
    // for(int i=0;i<=ans.length();i++)
    // count+=permutate_withRepet_void( str.substring(1) ,
    // ans.substring(0,i)+ch+ans.substring(i) );

    // approach 2 , sir's
    for (int i = 0; i < str.length(); i++) {
      count +=
        permutate_withRepet_void(
          str.substring(0, i) + str.substring(i + 1),
          ans + str.charAt(i)
        );
    }

    return count;
  }

  public static int permutate_withoutRepet_onlyVoid(String str, String ans) {
    if (str.length() == 0) {
      System.out.println(ans);
      return 1;
    }

    int count = 0;
    boolean[] arr = new boolean[26];

    for (boolean x : arr) {
      x = false;
    }

    for (int i = 0; i < str.length(); i++) {
      if (arr[str.charAt(i) - 'a'] == false) {
        count +=
          permutate_withoutRepet_onlyVoid(
            str.substring(0, i) + str.substring(i + 1),
            ans + str.charAt(i)
          );

        // i=0, a ke liye loop chlega,complete hoke vapis aaega, i=1 ,b ke liye chalgea,
        // complete grow krega , fr vapis aaaega, backtracking
        arr[str.charAt(i) - 'a'] = true;
      }
    }

    return count;
  }
}

class Solution {

  public int maxUncrossedLines_(int[] A, int[] B, int i, int j, int[][] dp) {
    for (int i = dp.length; i >= 0; i--) {
      for (int j = dp[i].length; j >= 0; j--) {
        if (i == A.length || j == B.length) return 0;

        int ans = 0;
        if (A[i] == B[j]) {
          ans = maxUncrossedLines_(A, B, i + 1, j + 1, dp) + 1;
        } else {
          ans =
            Math.max(
              maxUncrossedLines_(A, B, i + 1, j, dp),
              maxUncrossedLines_(A, B, i, j + 1, dp)
            );
        }
        dp[i][j] = ans;
      }
    }
    return dp[0][0];
  }

  public int maxUncrossedLines(int[] A, int[] B) {
    int a_len = A.length;
    int b_len = B.length;

    int[][] dp = new int[a_len + 1][b_len + 1];

    for (int i = 0; i < dp.length; i++) {
      for (int j = 0; j < dp[i].length; j++) {
        dp[i][j] = -1;
      }
    }

    return maxUncrossedLines_(A, B, 0, 0, dp);
  }
}
