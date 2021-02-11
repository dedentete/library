// soundhound2018-summer-qual D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

template <typename T>
vector<T> Dijkstra(int s, vector<vector<pair<int, T>>>& G
                   /*, vector<int> & prev*/) {
    const T INF = numeric_limits<T>::max();
    using P = pair<T, int>;
    int V = G.size();
    vector<T> dist(V, INF);
    priority_queue<P, vector<P>, greater<P>> que;
    dist[s] = 0;
    que.emplace(0, s);
    // prev.assign(V, -1);
    while (!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i = 0; i < (int)G[v].size(); i++) {
            int to = G[v][i].first;
            T cost = G[v][i].second;
            if (dist[to] > dist[v] + cost) {
                dist[to] = dist[v] + cost;
                // prev[to] = v;
                que.emplace(dist[to], to);
            }
        }
    }
    return dist;
}

signed main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--;
    t--;
    int u, v;
    ll a, b;
    using P = pair<int, ll>;
    vector<vector<P>> Ga(n), Gb(n);
    rep(i, m) {
        cin >> u >> v >> a >> b;
        u--;
        v--;
        Ga[u].emplace_back(v, a);
        Ga[v].emplace_back(u, a);
        Gb[u].emplace_back(v, b);
        Gb[v].emplace_back(u, b);
    }
    auto dista = Dijkstra(s, Ga), distb = Dijkstra(t, Gb);
    ll ans[n];
    for (int v = n - 1; v >= 0; v--) {
        ans[v] = (ll)1e15 - (dista[v] + distb[v]);
        if (v != n - 1) ans[v] = max(ans[v], ans[v + 1]);
    }
    rep(v, n) {
        cout << ans[v] << endl;
    }
    return 0;
}