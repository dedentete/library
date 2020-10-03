// ARC-30-C
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

struct SCC {
    int n, cnt;
    vector<vector<int>> G, R;
    vector<bool> used;
    vector<int> vs, cmp;

    SCC(int n) : n(n), G(n), R(n), used(n), cmp(n) {}

    int operator[](int k) {
        return cmp[k];
    };

    void add_edge(int from, int to) {
        G[from].emplace_back(to);
        R[to].emplace_back(from);
    }

    void dfs(int v) {
        used[v] = true;
        for (int u : G[v]) {
            if (!used[u]) dfs(u);
        }
        vs.emplace_back(v);
    }

    void rdfs(int v, int cnt) {
        used[v] = true;
        cmp[v] = cnt;
        for (int u : R[v]) {
            if (!used[u]) rdfs(u, cnt);
        }
    }

    int build() {
        for (int v = 0; v < n; v++) {
            if (!used[v]) dfs(v);
        }
        fill(used.begin(), used.end(), false);
        cnt = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (!used[vs[i]]) {
                rdfs(vs[i], cnt);
                cnt++;
            }
        }
        return cnt;
    }

    vector<vector<int>> makeGraph() {
        vector<vector<int>> res;
        res.resize(cnt, vector<int>());
        for (int v = 0; v < n; v++) {
            for (int u : G[v]) {
                if (cmp[v] != cmp[u]) res[cmp[v]].emplace_back(cmp[u]);
            }
        }
        for (int i = 0; i < cnt; i++) {
            sort(res[i].begin(), res[i].end());
            res[i].erase(unique(res[i].begin(), res[i].end()), res[i].end());
        }
        return res;
    }
};

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    char c[n];
    rep(i, n) {
        cin >> c[i];
    }
    SCC scc(n);
    int a, b;
    rep(i, m) {
        cin >> a >> b;
        a--;
        b--;
        scc.add_edge(a, b);
    }
    int cnt = scc.build();
    auto G = scc.makeGraph();
    string s[cnt];
    rep(i, n) {
        s[scc[i]].push_back(c[i]);
    }
    rep(i, cnt) {
        sort(ALL(s[i]));
    }
    string dp[cnt][k + 1];
    fill(dp[0], dp[cnt], "{");
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j <= (int)s[i].size(); j++) {
            dp[i][j] = s[i].substr(0, j);
        }
    }
    for (int from = 0; from < cnt; from++) {
        for (int to : G[from]) {
            for (int i = 0; i < k; i++) {
                for (int j = 0; j <= (int)s[to].size(); j++) {
                    if (i + j > k) continue;
                    dp[to][i + j] =
                        min(dp[to][i + j], dp[from][i] + s[to].substr(0, j));
                }
            }
        }
    }
    string ans = "{";
    for (int v = 0; v < cnt; v++) {
        ans = min(ans, dp[v][k]);
    }
    cout << (ans != "{" ? ans : "-1") << endl;
    return 0;
}