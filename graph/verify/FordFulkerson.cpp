// ABC-10-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
using P = pair<int, int>;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

/*
    有向グラフであることに注意 !!
    計算量 : O(FE)
*/
template <typename T>
struct FordFulkerson {
    struct edge {
        int to;
        T cap;
        int rev;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector<vector<edge>> G;
    vector<bool> used;

    FordFulkerson(int n) : G(n), used(n) {}

    void add_edge(int from, int to, T cap) {
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, 0, G[from].size() - 1);
    }

    T dfs(int v, int t, T f) {
        if (v == t) return f;
        used[v] = true;
        for (edge& e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    T flow(int s, int t, T INF = 1e9) {
        T fl = 0;
        while (true) {
            fill(used.begin(), used.end(), false);
            T f = dfs(s, t, INF);
            if (f == 0) break;
            fl += f;
        }
        return fl;
    }
};

signed main() {
    int n, g, e;
    cin >> n >> g >> e;
    FordFulkerson<int> ff(n + 1);
    int p;
    rep(i, g) {
        cin >> p;
        ff.add_edge(p, n, 1);
        ff.add_edge(n, p, 1);
    }
    int a, b;
    rep(i, e) {
        cin >> a >> b;
        ff.add_edge(a, b, 1);
        ff.add_edge(b, a, 1);
    }
    cout << ff.flow(0, n) << endl;
    return 0;
}