// tenka1-2015-quala C
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};

/*
    二部グラフの最大マッチングを求める
    O(VE)
*/
struct BiMatch {
    int V, time;
    vector<vector<int>> G;
    vector<int> match, used;
    vector<bool> dead;

    BiMatch(int V)
        : V(V), time(0), G(V), match(V, -1), used(V, -1), dead(V, false) {}

    void add_edge(int u, int v) {
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    bool dfs(int v) {
        used[v] = time;
        for (int u : G[v]) {
            if (dead[u]) continue;
            int w = match[u];
            if ((w < 0) || (used[w] < time && dfs(w))) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

    int build() {
        int res = 0;
        for (int v = 0; v < V; v++) {
            if (dead[v]) continue;
            if (match[v] < 0) {
                time++;
                res += dfs(v);
            }
        }
        return res;
    }
};

signed main() {
    int m, n;
    cin >> m >> n;
    int a[m][n], b[m][n];
    rep(i, m) {
        rep(j, n) {
            cin >> a[i][j];
        }
    }
    rep(i, m) {
        rep(j, n) {
            cin >> b[i][j];
        }
    }
    int cnt = 0;
    BiMatch bm(m * n);
    rep(y, m) {
        rep(x, n) {
            if (a[y][x] != b[y][x]) cnt++;
            if ((y + x) % 2 == 0) continue;
            rep(i, 4) {
                int ny = y + dy[i], nx = x + dx[i];
                if (ny < 0 || m <= ny || nx < 0 || n <= nx) continue;
                int odd = y * n + x, even = ny * n + nx;
                if (a[y][x] != a[ny][nx] && b[y][x] != b[ny][nx] &&
                    a[y][x] == b[ny][nx])
                    bm.add_edge(odd, even);
            }
        }
    }
    cout << cnt - bm.build() << endl;
    return 0;
}