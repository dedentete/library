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