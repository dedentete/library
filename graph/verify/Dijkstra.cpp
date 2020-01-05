//AOJ-GRL-1-A
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

template <typename T>
vector<T> Dijkstra(int s, vector<vector<pair<int, T>>> & G, /*vector<int> & prev,*/ const T INF = 1e9){
    using P = pair<T, int>;
    int V = G.size();
    vector<T> dist(V, INF);
    priority_queue<P, vector<P>, greater<P>> que;
    dist[s] = 0;
    que.emplace(0, s);
    /*prev.assign(V, -1);*/
    while(!que.empty()){
        P p = que.top();
        que.pop();
        int v = p.second;
        if(dist[v] < p.first) continue;
        for(int i = 0; i < G[v].size(); i++){
            int to = G[v][i].first;
            T cost = G[v][i].second;
            if(dist[to] > dist[v] + cost){
                dist[to] = dist[v] + cost;
                /*prev[to] = v;*/
                que.emplace(dist[to], to);
            }
        }
    }
    return dist;
}

signed main(){
    int v,e,r;
    cin >> v >> e >> r;
    using P = pair<int, ll>;
    vector<vector<P>> G(v);
    int s,t;
    ll d;
    REP(i,e){
        cin >> s >> t >> d;
        G[s].emplace_back(t, d);
    }
    vector<ll> dist = Dijkstra(r, G, LINF);
    REP(i,v){
        if(dist[i] == LINF){
            cout << "INF" << endl;
        }else{
            cout << dist[i] << endl;
        }
    }
    return 0;
}