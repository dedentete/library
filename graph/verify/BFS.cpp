// ABC-160-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
using P = pair<int, int>;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

vector<int> BFS(int s, vector<vector<int>>& G) {
    int V = G.size();
    const int INF = 1e9;
    vector<int> dist(V, INF);
    queue<int> que;
    que.emplace(s);
    dist[s] = 0;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int to : G[v]) {
            if (dist[to] == INF) {
                que.emplace(to);
                dist[to] = dist[v] + 1;
            }
        }
    }
    return dist;
}

signed main() {
    int n, x, y;
    cin >> n >> x >> y;
    x--;
    y--;
    vector<vector<int>> G(n);
    rep(i, n - 1) {
        G[i].emplace_back(i + 1);
        G[i + 1].emplace_back(i);
    }
    G[x].emplace_back(y);
    int ans[n] = {};
    rep(i, n) {
        vector<int> dist = BFS(i, G);
        for (int j = i + 1; j < n; j++) {
            ans[dist[j] - 1]++;
        }
    }
    rep(i, n - 1) {
        cout << ans[i] << endl;
    }
    return 0;
}