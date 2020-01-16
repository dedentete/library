//AOJ-GRL-3-C
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

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

signed main(){
    int V,E;
    cin >> V >> E;
    SCC scc(V);
    REP(i,E){
        int s,t;
        cin >> s >> t;
        scc.add_edge(s,t);
    }
    scc.build();
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << (scc[u] == scc[v]) << endl;
    }
    return 0;
}