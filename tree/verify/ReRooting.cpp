// EDPC-V
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
using P = pair<int, int>;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

template <typename T, typename ET>
struct ReRooting {
    struct edge {
        int to;
        ET data;
        edge(int to, ET data) : to(to), data(data) {}
    };

    using F = function<T(T, T)>;
    using L = function<T(T, ET)>;
    vector<vector<edge>> G;
    vector<T> dp, res;
    const T id;
    const F f;
    const L l;

    ReRooting(int V, const F f, const L l, const T id)
        : G(V), f(f), l(l), id(id), dp(V, id), res(V, id) {}

    void add_edge(int u, int v, ET c, ET cr) {
        G[u].emplace_back(v, c);
        G[v].emplace_back(u, cr);
    }

    void add_edge(int u, int v, ET c) {
        add_edge(u, v, c, c);
    }

    void dfs(int v, int pre) {
        for (auto e : G[v]) {
            if (e.to == pre) continue;
            dfs(e.to, v);
            dp[v] = f(dp[v], l(dp[e.to], e.data));
        }
    }

    void rdfs(int v, int pre) {
        for (auto e : G[v]) {
            res[v] = f(res[v], l(dp[e.to], e.data));
        }
        int n = G[v].size();
        vector<T> lsum(n + 1, id), rsum(n + 1, id);
        for (int i = 0; i < n; i++) {
            lsum[i + 1] = f(lsum[i], l(dp[G[v][i].to], G[v][i].data));
        }
        for (int i = n - 1; i >= 0; i--) {
            rsum[i] = f(rsum[i + 1], l(dp[G[v][i].to], G[v][i].data));
        }
        for (int i = 0; i < n; i++) {
            if (G[v][i].to == pre) continue;
            dp[v] = f(lsum[i], rsum[i + 1]);
            rdfs(G[v][i].to, v);
        }
    }

    vector<T> solve() {
        dfs(0, -1);
        rdfs(0, -1);
        return res;
    }
};

signed main() {
    int n;
    ll m;
    cin >> n >> m;
    auto f = [&](ll a, ll b) { return a * b % m; };
    auto l = [&](ll a, int b) { return (a + b) % m; };
    ReRooting<ll, int> rr(n, f, l, 1);
    int x, y;
    rep(i, n - 1) {
        cin >> x >> y;
        x--;
        y--;
        rr.add_edge(x, y, 1);
    }
    auto ans = rr.solve();
    rep(i, n) {
        cout << ans[i] << endl;
    }
    return 0;
}