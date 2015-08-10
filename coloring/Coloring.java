
import java.io.*;
import java.util.*;

class Graph {
    private final int N;
    private final int E;
    private List adj[] = null;
    private int color[] = null;

    public Graph(int N, int E) {
        this.N = N;
        this.E = E;
        this.adj = new List[N];
        this.color = new int[N];
        for(int i = 0; i < N; i++) {
            this.adj[i] = new ArrayList<Integer>();
            this.color[i] = -1;
        }

    }

    public void addEdge(int u, int v) {
        this.adj[u].add(v);
        this.adj[v].add(u);
    }

    public int color() {
        
    }

    public int getMaxDegree() {
        int u = -1;
        int r = -1;
        for(int i = 0; i < N; i++) {
            if(this.adj[i].size() > r) {
                u = i;
                r = this.adj[i].size();
            }
        }

        return u;
    }

    public int getMinDegree() {
        int u = -1;
        int r = this.N + 1;
        for(int i = 0; i < N; i++) {
            if(this.adj[i].size() < r) {
                u = i;
                r = this.adj[i].size();
            }
        }

        return u;
    }

    public void print() {
        System.out.println(String.format("%d %d", N, E));
        for(int i = 0; i < N; i++) {
            List<Integer> ii = (List<Integer>)this.adj[i];
            for(Integer j : ii) {
                System.out.println(String.format("%d %d", i, j));
            }
            
        }
    }
}

public class Coloring {

    public static void main(String args[]) {
        try(BufferedReader in = new BufferedReader(new FileReader(args[0]))) {
            int N, E;
            String line = null;
            line = in.readLine();
            if(line == null) 
                return;
            String tmp [] = line.split("\\s+");
            N = Integer.parseInt(tmp[0]);
            E = Integer.parseInt(tmp[1]);
            
            Graph g = new Graph( N, E );
            while( (line = in.readLine()) != null) {
                tmp = line.split("\\s+");
                N = Integer.parseInt(tmp[0]);
                E = Integer.parseInt(tmp[1]);
                g.addEdge(N, E);
            }
            System.out.println("MAX: " + g.getMaxDegree());
            System.out.println("MIN: " + g.getMinDegree());

            g.color();
        } catch(IOException ex) {
            System.err.println("Failed to open file " + args[0] + ". " + ex.getLocalizedMessage());
        }
        
    }
}
