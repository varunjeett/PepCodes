public class L015{
    
    public static class Node{
        int wordend;
        Node[] childs;

        Node(){
            this.wordend=0;
            this.childs=new Node[26];

        }
    }
    
    static Node root = null;

    public static void insert(String word,Node root) {

      Node cur = root;
      for(int i=0;i<word.length();i++)
      {
       if(cur.childs[word.charAt(i)-'a']==null) 
          cur.childs[word.charAt(i)-'a']=new Node();

        cur=cur.childs[word.charAt(i)-'a'];
      }
      cur.wordend++;
      System.out.println(cur.wordend);
    }
    
    public static boolean search_(String word, int idx, Node cur) {
                  
        if (idx == word.length()) {
         return (cur.wordend != 0);
        }
      
        boolean res = false;
      
        if (word.charAt(idx) == '.') 
        {
          for (int j = 0; j < 26; j++) 
          {
            if (cur.childs[j] != null)   
            {
                Node newroot=cur.childs[j];   
                res = res || search_(word, idx + 1,newroot);
            } 
          }   
           
        }  
         
        else 
        {
         
         int val = word.charAt(idx) - 'a';
      
         if (cur.childs[val] != null) 
            {
                Node newroot=cur.childs[val];
                res = res || search_(word, idx + 1,newroot);
            }
        
        }
        return res;
      
       }
      
       public static boolean search(String word) {
         return search_(word, 0, root);
       }

       public static boolean Prefix(String word, Node root) {

         Node cur = root;
         for (int i = 0; i < word.length(); i++) {
           if (cur.childs[word.charAt(i) - 'a'] == null)
             return false;
           else
             cur = cur.childs[word.charAt(i) - 'a'];
         }
         return true;

       }

       public static void solve() {
         root = new Node();
         insert("abc", root);
         insert("abbc", root);
         insert("apple", root);
         insert("pqrstv", root);

         System.out.println(search("abd"));



    }

    public static void main(String[] args) {
       solve();
    }

}