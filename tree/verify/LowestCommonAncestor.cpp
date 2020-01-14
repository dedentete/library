//PAST201912-K
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
};

signed main(){
    int n;
    cin >> n;
    int par;
    LCA lca(n);
    REP(i,n){
        int p;
        cin >> p;
        if(p == -1){
            par = i;
            continue;
        }
        p--;
        lca.add_edge(p, i);
    }
    lca.build(par);
    int q;
    cin >> q;
    REP(i,q){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        if(lca.query(a, b) == b) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}