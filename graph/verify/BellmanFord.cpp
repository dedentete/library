// AOJ-GRL-1-B
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a) for (int i = 0; i < (a); i++)
#define ALL(a) (a).begin(), (a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

template <typename T>
struct edge {
    int from, to;
    T cost;
    edge(int from, int to, T cost = 1) : from(from), to(to), cost(cost) {}
    bool operator<(const edge& e) const {
        return cost < e.cost;
    }
};

/*
    sからたどりつける負の閉路を検出したとき、空の vector を返す
    頂点数 V, 始点 s, 辺の集合 es, INF として LINF を使うとき :
    vector<ll> dist = BellmanFord(V, s, es, LINF);
*/
template <typename T>
vector<T> BellmanFord(int V, int s, vector<edge<T>>& es, const T INF = 1e9) {
    int E = es.size();
    vector<T> dist(V, INF);
    dist[s] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (edge<T>& e : es) {
            if (dist[e.from] == INF) continue;
            dist[e.to] = min(dist[e.to], dist[e.from] + e.cost);
        }
    }
    for (edge<T>& e : es) {
        if (dist[e.from] == INF) continue;
        if (dist[e.from] + e.cost < dist[e.to]) return vector<T>();
    }
    return dist;
}

//グラフ全体をみて、負の閉路が存在するとき true を返す
template <typename T>
bool FindNegativeLoop(int V, vector<edge<T>>& es) {
    vector<T> dist(V, 0);
    for (int i = 0; i < V; i++) {
        for (edge<T>& e : es) {
            if (dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                if (i == V - 1) return true;
            }
        }
    }
    return false;
}

signed main() {
    int v, e, r;
    cin >> v >> e >> r;
    int s, t;
    ll d;
    vector<edge<ll>> es;
    REP(i, e) {
        cin >> s >> t >> d;
        es.emplace_back(s, t, d);
    }
    vector<ll> dist = BellmanFord(v, r, es, LINF);
    if (dist.size() == 0) {
        cout << "NEGATIVE CYCLE" << endl;
    } else {
        REP(i, v) {
            if (dist[i] == LINF)
                cout << "INF" << endl;
            else
                cout << dist[i] << endl;
        }
    }
    return 0;
}