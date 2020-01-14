//ABC-14-D
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

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

    int query(int u, int v){
        if(depth[u] > depth[v]) swap(u, v);
        for(int k = 0; k < h; k++){
            if((depth[v] - depth[u]) >> k & 1) v = par[k][v];
        }
        if(u == v) return u;
        for(int k = h - 1; k >= 0; k--){
            if(par[k][u] != par[k][v]){
                u = par[k][u];
                v = par[k][v];
            }
        }
        return par[0][u];
    }

    int dist(int u, int v){
        return depth[u] + depth[v] - depth[query(u, v)] * 2;
    }
};

signed main(){
    int n;
    cin >> n;
    LCA lca(n);
    REP(i,n - 1){
        int x,y;
        cin >> x >> y;
        x--;
        y--;
        lca.add_edge(x, y);
    }
    lca.build();
    int q;
    cin >> q;
    while(q--){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        cout << lca.dist(a, b) + 1 << endl;
    }
    return 0;
}