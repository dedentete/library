//AOJ-GRL-7-A
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

struct BiMatch{
    int V, time;
    vector<vector<int>> G;
    vector<int> match, used;
    vector<bool> dead;

    BiMatch(int V) : V(V), time(0), G(V), match(V, -1), used(V, -1), dead(V, false){} 

    void add_edge(int u, int v){
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    bool dfs(int v){
        used[v] = time;
        for(int u : G[v]){
            if(dead[u]) continue;
            int w = match[u];
            if((w < 0) || (used[w] < time && dfs(w))){
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

    int build(){
        int res = 0;
        for(int v = 0; v < V; v++){
            if(dead[v]) continue;
            if(match[v] < 0){
                time++;
                res += dfs(v);
            }
        }
        return res;
    }
};

signed main(){
    int X,Y,e;
    cin >> X >> Y >> e;
    int V = X + Y;
    BiMatch bi(V);
    int x,y;
    REP(i,e){
        cin >> x >> y;
        bi.add_edge(x, X + y);
    }
    cout << bi.build() << endl;
    return 0;
}