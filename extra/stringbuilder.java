//flip game lintcode=========================
public class Solution {
    
    public List<String> generatePossibleNextMoves(String s) {
        // write your code here
        
        
        List<String> ll=new ArrayList<>();
        for(int i=0; i < s.length()-1; i++){
            if(s.charAt(i)=='+'){
                if(s.charAt(i+1)=='+'){
                    StringBuilder str=new StringBuilder(s);
                    str.setCharAt(i,'-');
                    str.setCharAt(i+1,'-');
                    ll.add(str.toString());
                }
            }
        }
        
        return ll;
    }
}


//using toCharArray()
public class Solution {
 
    public List<String> generatePossibleNextMoves(String s) {
        // write your code here
        
        
        List<String> ll=new ArrayList<>();
        
        for(int i=0; i < s.length()-1; i++){
            if(s.charAt(i)=='+'){
                if(s.charAt(i+1)=='+'){
                char[] arr = s.toCharArray();
                arr[i] = '-';
                arr[i+1] = '-';
                String addIt= String.valueOf(arr);
                ll.add(addIt);
                }
            }
        }
        
        return ll;
    }
}



