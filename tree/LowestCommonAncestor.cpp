struct LCA{
    int n,h;
    vector<vector<int>> G,par;
    vector<int> depth;

    LCA(int n) : n(n), G(n), depth(n){
        h = 1;
        while((1 << h) <= n) h++;
        par.assign(h, vector<int>(n, -1));
    }

    void add_edge(int u, int v){
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void dfs(int v, int p, int d){
        par[0][v] = p;
        depth[v] = d;
        for(int u : G[v]){
            if(u != p) dfs(u, v, d + 1);
        }
    }

    void build(int r = 0){
        dfs(r, -1, 0);
        for(int k = 0; k + 1 < h; k++){
            for(int v = 0; v < n; v++){
                if(par[k][v] != -1) par[k + 1][v] = par[k][par[k][v]];
            }
        }
    }