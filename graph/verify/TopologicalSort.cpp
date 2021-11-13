// past202107-J
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int MOD = 1000000007;

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

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    int u, v;
    rep(i, m) {
        cin >> u >> v;
        u--, v--;
        G[u].emplace_back(v);
    }
    cout << ((int)Tsort(G).size() != n ? "Yes" : "No") << endl;
    return 0;
}