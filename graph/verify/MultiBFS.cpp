// PAST202012-I
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

vector<int> MultiBFS(vector<int> vs, vector<vector<int>>& G) {
    int V = G.size();
    vector<int> dist(V, -1);
    queue<int> que;
    for (int s : vs) {
        que.emplace(s);
        dist[s] = 0;
    }
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int to : G[v]) {
            if (dist[to] != -1) continue;
            que.emplace(to);
            dist[to] = dist[v] + 1;
        }
    }
    return dist;
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    int h[n];
    vector<int> c(k);
    rep(i, n) {
        cin >> h[i];
    }
    rep(i, k) {
        cin >> c[i];
        c[i]--;
    }
    vector<vector<int>> G(n);
    int a, b;
    rep(i, m) {
        cin >> a >> b;
        a--;
        b--;
        if (h[a] < h[b])
            G[a].emplace_back(b);
        else
            G[b].emplace_back(a);
    }
    auto dist = MultiBFS(c, G);
    rep(v, n) {
        cout << dist[v] << endl;
    }
    return 0;
}