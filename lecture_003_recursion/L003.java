import java.util.ArrayList;
import java.util.Scanner;

public class L003 {
     
    public static Scanner scn=new Scanner(System.in);

    static String [] dir_Name={"U","ur","R","dr","D","dl","L","ul"};
  
    static int[][]  dir_V={ {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
    
    static class pair{
      int length;
      String path;
      
      public pair(){
        this.length=0;
        this.path="";
      }

      public pair(int len,String pat){

        this.length=len;
        this.path=pat;
      }

      public  void display(){
        
        System.out.println("length is "+ length);
        System.out.println("path is "+ path);
      }
    }
  
    static boolean isValid(int r,int c, int[][] board){
   
        if(r>=0  && c>=0 && r<board.length && c<board[0].length && board[r][c]==1){
        return true;
        }
        else return false;  
   
    }

    static void floodfill(){
         
        int sr=0,sc=0,er=3,ec=3;
        int[][] board={ {1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1} };
       
        // int res=floodfill_height(sr,sc,er,ec,board);
        // System.out.println(res);
        
        pair ans=floodfill_max(sr, sc, er, ec, board);
        ans.display();
    }

    static int floodfill_height(int sr,int sc,int er,int ec,int[][] board){

        if(sr==er && sc==ec){
            return 0;
        }
        
        board[sr][sc]=0;   //visited
        
        int maxHeight=0;
        
        for(int i=0;i<dir_Name.length;i++){
          
            int r= sc + dir_V[i][0];
            int c= sr + dir_V[i][1];
            if( isValid(r, c, board) ){
              int curr_Max=floodfill_height(r,c,er,ec,board);
              maxHeight=Math.max(curr_Max,maxHeight);
            }
        }
        
        board[sr][sc]=1;  //unvisited
        return maxHeight+1;
        
    }
    
    static pair floodfill_max(int sr,int sc,int er,int ec,int[][] board){

        if(sr==er && sc==ec){
            pair base=new pair();
            return base;
        }

        board[sr][sc]=0;   //visited
        pair curr_max=new pair();
        

        for(int i=0;i<dir_Name.length;i++){
          
            int r= sc + dir_V[i][0];
            int c= sr + dir_V[i][1];
            
            if( isValid(r, c, board) ){
               pair smallAns=floodfill_max(r,c,er,ec,board);
              
               if(smallAns.length+1 >curr_max.length){
                   curr_max.length=smallAns.length+1;
                   curr_max.path=smallAns.path+dir_Name[i];
               }
               
            
            }    
        }

        board[sr][sc]=1;  //unvisited
        return curr_max;
    }
  
    static int permutation_infinite(int []coins, int target,String ans){  
        
        if(target==0){
            
            System.out.println(ans);
            return 1;
        
        }
       
        int count=0;
        
        for(int i=0; i<coins.length; i++){
           
            if(target-coins[i]>=0)
            count+=permutation_infinite( coins, target-coins[i] , ans+coins[i] );
    
        }

        return count;
    }
    
    static int permutation_finite(int[] coins,int [] available,int target,String ans){

        if(target==0){
            System.out.println(ans);
            return 1;
        }


        int count=0;
        
        for(int i=0;i<coins.length;i++){
           
            if ( available[i]>0   &&  target-coins[i]>=0 ) {
                
                available[i]--;
                count+=permutation_finite(coins, available, target-coins[i], ans+coins[i]);
                available[i]++;
           
            }
        
        }

        return count;
    }

   
    static void coinChange(){
        
        //int target=scn.nextInt();
        
        
        int[] coins={2,3,5,7};
        int[] available={1,1,1,1};               //no of coins available
      //  int answer=permutation_infinite(coins,10,"");
        int answer=permutation_finite(coins, available, 10 , "");
        System.out.println(answer);   

    }

    
    public static void main(String[] args){
       
        //floodfill();
     
        coinChange();
       
    }
         
}