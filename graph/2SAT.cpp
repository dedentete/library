struct SCC{
    int n;
    vector<vector<int>> G,R;
    vector<int> vs, cmp;
    vector<bool> used;

    SCC(int n) : n(n), G(n), R(n), used(n), cmp(n){}

    int operator [] (int k) { return cmp[k]; };

    void add_edge(int u, int v){
        G[u].emplace_back(v);
        R[v].emplace_back(u);
    }

    void dfs(int v){
        used[v] = true;
        for(int u : G[v]){
            if(!used[u]) dfs(u);
        }
        vs.emplace_back(v);
    }

    void rdfs(int v, int k){
        used[v] = true;
        cmp[v] = k;
        for(int u : R[v]){
            if(!used[u]) rdfs(u, k);
        }
    }

    int build(){
        for(int v = 0; v < n; v++){
            if(!used[v]) dfs(v);
        }
        fill(used.begin(), used.end(), false);
        int k = 0;
        for(int i = n - 1; i >= 0; i--){
            if(!used[vs[i]]){
                rdfs(vs[i], k);
                k++;
            }
        }
        return k;
    }
};

struct TwoSAT{
    int n;
    SCC scc;

    TwoSAT(int n) : n(n), scc(n * 2){}

    int neg(int v){ return(n + v) % (n * 2); }

    void add_if(int a, int b){
        // a -> b <=> !b -> !a
        scc.add_edge(a, b);
        scc.add_edge(neg(a), neg(b));
    }

    void add_or(int a, int b){
        // a or b <=> !a -> b
        add_if(neg(a), b);
    }

    void add_nand(int a, int b){
        // a nand b <=> a -> !b
        add_if(a, neg(b));
    }

    void set_true(int a){
        // a <=> !a -> a
        scc.add_edge(neg(a), a);
    }

    void set_false(int a){
        // !a <=> a -> !a
        scc.add_edge(a, neg(a));
    }

    vector<bool> build(){
        scc.build();
        vector<bool> res(n);
        for(int i = 0; i < n; i++){
            if(scc[i] == scc[n + i]) return{};
            res[i] = scc[i] > scc[n + i];
        }
        return res;
    }
};