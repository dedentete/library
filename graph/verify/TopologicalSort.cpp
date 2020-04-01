// ABC-139-E
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a) for (int i = 0; i < (a); i++)
#define ALL(a) (a).begin(), (a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

const int MAX_V = 1000 * (1000 - 1) / 2;

int ans = 0;

/*
    To.size() == V
   であればトポロジカルソートができた、そうでなければできなかったと判定できる
*/
vector<int> Tsort(vector<vector<int>>& G) {
    vector<int> To;
    int V = G.size();
    stack<int> st;
    int indeg[V] = {};
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            indeg[G[i][j]]++;
        }
    }
    for (int i = 0; i < V; i++) {
        if (indeg[i] == 0) {
            st.push(i);
        }
    }
    vector<int> dp(V);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        To.push_back(u);
        for (int i = 0; i < G[u].size(); i++) {
            indeg[G[u][i]]--;
            dp[G[u][i]] = max(dp[G[u][i]], dp[u] + 1);
            ans = max(ans, dp[G[u][i]]);
            if (indeg[G[u][i]] == 0) {
                st.push(G[u][i]);
            }
        }
    }
    return To;
}

signed main() {
    int n;
    cin >> n;
    int id[n][n];
    int V = 0;
    REP(i, n) {
        for (int j = i + 1; j < n; j++) {
            id[i][j] = V;
            V++;
        }
    }
    int num[n][n - 1];
    int a, b;
    REP(i, n) {
        REP(j, n - 1) {
            cin >> a;
            a--;
            b = i;
            if (a > b) {
                swap(a, b);
            }
            num[i][j] = id[a][b];
        }
    }
    vector<vector<int>> G(V);
    REP(i, n) {
        REP(j, n - 2) {
            G[num[i][j]].push_back(num[i][j + 1]);
        }
    }
    vector<int> To = Tsort(G);
    if (To.size() != V) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans + 1 << endl;
    return 0;
}