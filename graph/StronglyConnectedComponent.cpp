struct SCC {
    int n;
    vector<vector<int>> G, R;
    vector<int> vs, cmp;
    vector<bool> used;

    SCC(int n) : n(n), G(n), R(n), used(n), cmp(n) {}

    int operator[](int k) {
        return cmp[k];
    };

    void add_edge(int u, int v) {
        G[u].emplace_back(v);
        R[v].emplace_back(u);
    }

    void dfs(int v) {
        used[v] = true;
        for (int u : G[v]) {
            if (!used[u]) dfs(u);
        }
        vs.emplace_back(v);
    }

    void rdfs(int v, int k) {
        used[v] = true;
        cmp[v] = k;
        for (int u : R[v]) {
            if (!used[u]) rdfs(u, k);
        }
    }

    int build() {
        for (int v = 0; v < n; v++) {
            if (!used[v]) dfs(v);
        }
        fill(used.begin(), used.end(), false);
        int k = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (!used[vs[i]]) {
                rdfs(vs[i], k);
                k++;
            }
        }
        return k;
    }
};