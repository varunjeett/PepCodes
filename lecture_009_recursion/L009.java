

public class L009{
    
    public static void main(String[] args) {
        solve();  
    }

    public static void solve(){

        //crypt("send","more","money");
        crossword();

    }

    public static int [] mapping ;
    public static int numused ;
    
    public static void crypt(String a, String b, String c) {
        
        String str= a + b + c;
        
        int freq = 0;
    
        for( int i= 0 ; i<str.length() ; i++ ){

            int idx = str.charAt(i) - 'a';
            freq =  ( freq | (1<<idx) );

        }
        
        String unique = "";

        for (int i = 0;i < 26 ;i++ )
        {
            int mask  = (1<<i);

            if( (freq & mask)!=0)
            {
                unique += (char)(i+'a');
            }
        }
        
        mapping = new int [26];
        numused = 0;
       
        for(int i = 0 ; i<mapping.length ; i++)
        {
           mapping[i] = 0;
        }

        System.out.println( cryptarthmetic (unique , unique.length() , 0 ,0 ,a,b,c) );
  
    }

    public static int cryptarthmetic(String str ,int len , int idx ,int val ,String a, String b, String c){
        
        if( val>9 || idx == len )
        {
            if(idx == len)
            {
                int num1 = stringtoNUM(a) ;
                int num2 = stringtoNUM(b) ;
                int num3 = stringtoNUM(c) ;

                if( num1+num2==num3 && mapping[a.charAt(0)-'a']!=0 && mapping[b.charAt(0)-'a']!=0 && mapping[c.charAt(0)-'a']!=0 )
                {
                    System.out.println(a + " -> " + num1);
                    System.out.println(b + " -> " + num2);
                    System.out.println(c + " -> " + num3);
                    return 1;
                }
            }
            return 0 ;
        }
        
        int count=0;

        int mask = (1<<val);

        if( (numused & mask)==0)
        {  
            numused = (numused^mask);
           
            mapping[str.charAt(idx)-'a'] = val;
            
            count+=cryptarthmetic(str , len , idx+1 , 0 , a  ,b , c);
            
            mapping[str.charAt(idx)-'a'] = 0;
            
            numused = (numused^mask);
        }
        
        count+=cryptarthmetic(str, len, idx , val+1 , a  ,b , c);

        return count;

    }
    
    public static int stringtoNUM(String s){
        
       
        int ans=0;

        for(int i = 0 ; i<s.length() ; i++)
        {
            int idx = s.charAt(i) - 'a';
            ans = ans*10 + mapping[idx];
        }
        return ans;
    }
    
    //crossword.===========================================================
    
    public static void crossword(){

char [][] board ={{'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '-'},
        {'+', '-', '-', '-', '-', '-', '-', '-', '+', '-'},
        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '-'},
        {'+', '-', '+', '+', '+', '+', '+', '+', '+', '-'},
        {'+', '-', '-', '-', '-', '-', '-', '+', '+', '-'},
        {'+', '-', '+', '+', '+', '-', '+', '+', '+', '-'},
        {'+', '+', '+', '+', '+', '-', '+', '+', '+', '-'},
        {'+', '+', '+', '+', '+', '-', '+', '+', '+', '-'},
        {'+', '+', '+', '+', '+', '+', '+', '+', '+', '-'}};

       
        
        String [] words = {"abhijeetaa","agra", "norway", "england", "gwalior","leabcdefga"};
        
        crossword_fill(board,words,0);
        
    }

    public static boolean canPlaceH(int r , int c , String word , char [][] board){
       
        if(c==0 && word.length()<board[0].length)   //word starting at the begin of board, end ke baad vala check krenge
       {
           if(board[r][c+word.length()]!='+')
           {
               return false;
           }
       }

       else if( (c+word.length()==board[0].length) && word.length()<board[0].length )  // word ending at the begin of board, begin se phle vala check krenge
       {
           if(board[r][c-1]!='+')
           {
               return false;
           }
       }

       else //word in strictly middle
       { 
            if( ( (c-1)>=0  && board[r][c-1]!='+' ) || ( c+word.length() < board[0].length && board[r][c+word.length()]!='+' ) ) 
            {
                return false;
            }
        }
        
        for(int i = 0;i<word.length();i++)
        {   
            if((c+i)>board[0].length)
               return false;

            if( (c+i)<board[0].length && board[r][c+i]!='-' &&  board[r][c+i]!=word.charAt(i) )
            {
                return false;
            }
        }

       return true;
    }    

    public static boolean canPlaceV(int r , int c  , String word, char [][] board ){
       
       if( r==0 && word.length()<board.length )
       {
           if( board[r+word.length()][c]!='+')
           {
               return false;
           }
       }
       else if( (r+word.length()==board.length) && word.length()<board.length )
       {
           if( board[r-1][c]!='+')
           {
               return false;
           }
       }
       else 
       {
         if( ( (r-1>=0) && board[r-1][c]!='+' ) || ( r+word.length() <board.length && board[r+word.length()][c]!='+' )  )
         {
               return  false;
         }
       }
       for(int i = 0;i<word.length();i++)
       {   
           if( (r+i)>board.length )
               return false;

           if( (r+i<board.length) && board[r+i][c]!='-' && board[r+i][c]!=word.charAt(i) )
           {
               return false;
           }
       }

       return true;
    }

    public static boolean[] PlacewordH(int r , int c , String word, char [][] board ){
       
        boolean [] mark = new boolean[word.length()];
        for(int j = 0;j<word.length();j++) 
            mark[j]=false;
        
        for(int i = 0 ; i < word.length(); i++)
        {
            if( board[r][c+i]=='-' )
            {
                mark[i]=true;
                board[r][c+i]=word.charAt(i);
            
            }
        }

        return mark;

    }

    public static boolean[] PlacewordV(int r , int c , String word, char [][] board){

        boolean [] mark = new boolean[word.length()];
        for(int j = 0;j<word.length();j++) 
            mark[j]=false;
        
        for(int i = 0 ; i < word.length(); i++)
        {
            if( board[r+i][c]=='-' )  ///kyunki sirf yhi par humne apna letter rkha hai
            {
                mark[i]=true;  
                board[r+i][c]=word.charAt(i);
            }
        }

        return mark;

    }
    
    public static void unPlacewordH(int r , int c  , String word, char [][]  board , boolean[] mark){
        
        for(int i = 0;i<word.length();i++)
        {
            if(mark[i])
            {
                board[r][c+i]='-';
            }
        }
    }
    
    public static void unPlacewordV(int r , int c , String word, char [][]  board , boolean[] mark){
        
        for(int i = 0;i<word.length();i++)
        {
            if(mark[i])
            {
                board[r+i][c]='-';
            }
        }

    }

    public static int crossword_fill(char [][] board , String [] words, int idx){
        
        if(idx==words.length){
            
            for(char [] ch:board)
            {   
                System.out.println(ch);
            }
            return 1;
        }
         
        int count = 0;

        for(int i = 0;i<board.length;i++){
           
            for(int j = 0;j<board[i].length;j++){

                if( board[i][j]=='-' || board[i][j]==words[idx].charAt(0) )
                {
                   if(canPlaceH(i, j, words[idx], board))  
                   {
                       boolean [] arr = PlacewordH(i, j, words[idx], board);

                       count += crossword_fill(board ,  words,  idx+1);

                       unPlacewordH(i, j, words[idx] , board , arr);
                   }

                   if(canPlaceV(i, j, words[idx], board))  
                   {
                    boolean [] arr =  PlacewordV(i, j, words[idx], board);

                    count += crossword_fill(board ,  words,  idx+1);
                    
                    unPlacewordV(i, j, words[idx], board , arr);
                   }

                }
            }
        }

        return count;

    }

     
}