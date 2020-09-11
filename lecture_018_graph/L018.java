//2d arraylist 
import java.util.ArrayList;

import java.util.Scanner;

public class L018 {
    
    public static Scanner scn = new Scanner(System.in);
    public static void main(String[] args) {
        solve();
    }

    public static void solve(){
    System.out.println(journeyMoon());   
    }

    public static long journeyMoon(){
        
        int n , p , i , j;
        int a , b;

        n = scn.nextInt();
        p = scn.nextInt();
        //till line 30 , only graph creation
        ArrayList < ArrayList < Integer > > astronaut = new ArrayList< ArrayList < Integer > >() ;

        for(i = 0; i<n ;i++)
        {
            astronaut.add( new ArrayList <Integer>() );
        }

        for(i = 0 ; i< p; i++ )
        {
          a = scn.nextInt();
          b = scn.nextInt();
          
          astronaut.get(a).add(b);
          astronaut.get(b).add(a);
     
        }
        
        boolean [] vis = new boolean [n];

        ArrayList <Integer> countrysize = new ArrayList<Integer>();
        
        for( i = 0; i<n ;i++)
        {   
            if( vis[i] == false )
            {
              countrysize.add(journeyMoonDFS( i , astronaut , vis ));  
            }

        }
        int total = n;
        long ans = 0;
        for(i = 0 ; i < countrysize.size()  ; i++)
        {
            total = total - countrysize.get(i);
            ans = ans + ( total * countrysize.get(i) ); 
        }
       return ans;
    }

    public static int journeyMoonDFS(int src , ArrayList < ArrayList < Integer > > astronaut , boolean [] vis )
    {   
        vis[src] = true;
        
        int count = 0;

        for(int i = 0 ; i < astronaut.get(src).size(); i++ )
        {
            if( vis[astronaut.get(src).get(i)] == false )
            {
               count += journeyMoonDFS(astronaut.get(src).get(i),astronaut,vis);
            }
        }
        
        return count+1;
    }
}