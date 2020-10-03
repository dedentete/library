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