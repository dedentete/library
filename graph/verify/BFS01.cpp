// typical90-54
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int MOD = 1000000007;

vector<int> BFS01(int s, vector<vector<pair<int, int>>>& G) {
    int V = G.size();
    vector<int> dist(V, -1);
    deque<int> que;
    dist[s] = 0;
    que.push_front(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop_front();
        for (int i = 0; i < (int)G[v].size(); i++) {
            int to = G[v][i].first, cost = G[v][i].second;
            if (dist[to] != -1) continue;
            if (cost == 1) {
                dist[to] = dist[v] + 1;
                que.push_back(to);
            } else {
                dist[to] = dist[v];
                que.push_front(to);
            }
        }
    }
    return dist;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> G(n + m);
    rep(i, m) {
        int k;
        cin >> k;
        int r;
        rep(j, k) {
            cin >> r;
            r--;
            G[r].emplace_back(n + i, 1);
            G[n + i].emplace_back(r, 0);
        }
    }
    auto dist = BFS01(0, G);
    rep(i, n) {
        cout << dist[i] << endl;
    }
    return 0;
}