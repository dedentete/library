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