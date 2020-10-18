template <typename T>
T TSP(int s, vector<vector<pair<int, T>>>& G, const T INF = 1e9) {
    int V = G.size();
    vector<vector<T>> dp(1 << V, vector<T>(V, INF));
    dp[0][s] = 0;
    for (int bit = 0; bit < 1 << V; bit++) {
        for (int v = 0; v < V; v++) {
            for (auto p : G[v]) {
                int to = p.first, dist = p.second;
                if (bit & 1 << to) continue;
                dp[bit | 1 << to][to] =
                    min(dp[bit | 1 << to][to], dp[bit][v] + dist);
            }
        }
    }
    return dp[(1 << V) - 1][s];
}