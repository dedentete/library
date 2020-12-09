// ABC-186-E
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};

vector<int> BFS01(int s, vector<vector<pair<int, int>>>& G,
                  const int INF = 1e9) {
    int V = G.size();
    vector<int> dist(V, INF);
    deque<int> que;
    dist[s] = 0;
    que.push_front(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop_front();
        for (int i = 0; i < (int)G[v].size(); i++) {
            int to = G[v][i].first, cost = G[v][i].second;
            if (dist[to] != INF) continue;
            if (cost == 1) {
                que.push_back(to);
                dist[to] = dist[v] + 1;
            } else {
                que.push_front(to);
                dist[to] = dist[v];
            }
        }
    }
    return dist;
}

signed main() {
    int h, w;
    cin >> h >> w;
    string a[h];
    rep(i, h) {
        cin >> a[i];
    }
    auto f = [&](int y, int x) { return y * w + x; };
    vector<vector<pair<int, int>>> G(h * w + 26);
    int s = -1, g = -1;
    rep(i, h) {
        rep(j, w) {
            if (a[i][j] == '#') continue;
            if (a[i][j] == 'S') {
                s = f(i, j);
            } else if (a[i][j] == 'G') {
                g = f(i, j);
            } else if ('a' <= a[i][j] && a[i][j] <= 'z') {
                G[f(i, j)].emplace_back(h * w + a[i][j] - 'a', 1);
                G[h * w + a[i][j] - 'a'].emplace_back(f(i, j), 0);
            }
            rep(k, 4) {
                int ny = i + dy[k], nx = j + dx[k];
                if (0 <= ny && ny < h && 0 <= nx && nx < w &&
                    a[ny][nx] != '#') {
                    G[f(i, j)].emplace_back(f(ny, nx), 1);
                }
            }
        }
    }
    auto dist = BFS01(s, G);
    cout << (dist[g] != INF ? dist[g] : -1) << endl;
    return 0;
}