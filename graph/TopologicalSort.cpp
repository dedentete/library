// To.size() == V
// であればトポロジカルソートができた、そうでなければできなかったと判定できる
vector<int> Tsort(vector<vector<int>>& G) {
    vector<int> To;
    int V = G.size();
    stack<int> st;
    int indeg[V] = {};
    for (int v = 0; v < V; v++) {
        for (int u : G[v]) {
            indeg[u]++;
        }
    }
    for (int v = 0; v < V; v++) {
        if (indeg[v] == 0) {
            st.emplace(v);
        }
    }
    // vector<int> dp(V);
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        To.push_back(v);
        for (int u : G[v]) {
            indeg[u]--;
            // dp[u] = max(dp[u], dp[v] + 1);
            // ans = max(ans, dp[u]);
            if (indeg[u] == 0) {
                st.emplace(u);
            }
        }
    }
    return To;
}