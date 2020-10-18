// ABC180-E
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

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

signed main() {
    int n;
    cin >> n;
    int x[n], y[n], z[n];
    rep(i, n) {
        cin >> x[i] >> y[i] >> z[i];
    }
    vector<vector<pair<int, ll>>> G(n);
    rep(i, n) {
        rep(j, n) {
            G[i].emplace_back(
                j, abs(x[i] - x[j]) + abs(y[i] - y[j]) + max(0, z[j] - z[i]));
        }
    }
    cout << TSP(0, G, LINF) << endl;
    return 0;
}