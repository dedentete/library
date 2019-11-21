template <typename T>
struct FordFulkerson{
    struct edge{
        int to;
        T cap;
        int rev;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };
    
    vector<vector<edge>> G;
    vector<bool> used;

    FordFulkerson(int n) : G(n), used(n) {}

    void add_edge(int from, int to, T cap){
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, 0, G[from].size() - 1);
    }

    T dfs(int v, int t, T f){
        if(v == t) return f;
        used[v] = true;
        for(int i = 0; i < G[v].size(); i++){
            edge & e = G[v][i];
            if(!used[e.to] && e.cap > 0){
                T d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    T flow(int s, int t, T INF = 1e9){
        int fl = 0;
        while(true){
            fill(used.begin(), used.end(), false);
            T f = dfs(s, t, INF);
            if(f == 0) break;
            fl += f;
        }
        return fl;
    }
};