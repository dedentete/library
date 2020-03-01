/*
    有向グラフであることに注意 !!
    計算量 : O(EV^2)
*/
template <typename T>
struct Dinic{
    struct edge{
        int to;
        T cap;
        int rev;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector<vector<edge>> G;
    vector<int> level, itr;

    Dinic(int n) : G(n), level(n), itr(n) {}

    void add_edge(int from, int to, T cap){
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, 0, G[from].size() - 1);
    }

    void bfs(int s){
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        que.emplace(s);
        level[s] = 0;
        while(!que.empty()){
            int v = que.front();
            que.pop();
            for(edge & e : G[v]){
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    T dfs(int v, int t, T f){
        if(v == t) return f;
        for(edge & e : G[v]){
            if(e.cap > 0 && level[v] < level[e.to]){
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
        T fl = 0;
        while(true){
            bfs(s);
            if(level[t] < 0) return fl;
            fill(itr.begin(), itr.end(), 0);
            T f;
            while((f = dfs(s, t, INF)) > 0){
                fl += f;
            }
        }
        return fl;
    }
};