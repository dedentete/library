// AOJ-GRL-5-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

// https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
class HLD {
   private:
    void dfs_sz(int v) {
        auto &es = G[v];
        if (~par[v]) es.erase(find(es.begin(), es.end(), par[v]));

        for (int &u : es) {
            par[u] = v;
            dfs_sz(u);
            sub[v] += sub[u];
            if (sub[u] > sub[es[0]]) swap(u, es[0]);
        }
    }

    void dfs_hld(int v, int &pos) {
        vid[v] = pos++;
        inv[vid[v]] = v;
        for (int u : G[v]) {
            if (u == par[v]) continue;
            nxt[u] = (u == G[v][0] ? nxt[v] : u);
            dfs_hld(u, pos);
        }
    }

   public:
    vector<vector<int> > G;

    // vid: vertex -> idx
    // inv: idx -> vertex
    vector<int> vid, nxt, sub, par, inv;

    HLD(int n) : G(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    void add_edge(int u, int v) {
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void build(int r = 0) {
        int pos = 0;
        dfs_sz(r);
        nxt[r] = r;
        dfs_hld(r, pos);
    }

    int lca(int u, int v) {
        while (1) {
            if (vid[u] > vid[v]) swap(u, v);
            if (nxt[u] == nxt[v]) return u;
            v = par[nxt[v]];
        }
    }

    template <typename F>
    void for_each(int u, int v, const F &f) {
        while (1) {
            if (vid[u] > vid[v]) swap(u, v);
            f(max(vid[nxt[v]], vid[u]), vid[v] + 1);
            if (nxt[u] != nxt[v])
                v = par[nxt[v]];
            else
                break;
        }
    }

    template <typename F>
    void for_each_edge(int u, int v, const F &f) {
        while (1) {
            if (vid[u] > vid[v]) swap(u, v);
            if (nxt[u] != nxt[v]) {
                f(vid[nxt[v]], vid[v] + 1);
                v = par[nxt[v]];
            } else {
                if (u != v) f(vid[u] + 1, vid[v] + 1);
                break;
            }
        }
    }
};

template <typename T>
struct BIT {
    int n;
    vector<T> dat;

    BIT(int n) : n(n), dat(n + 1, 0) {}

    T sum(int idx) {  // 1-indexed
        T res(0);
        for (int i = idx; i > 0; i -= i & -i) res += dat[i];
        return res;
    }

    T sum(int l, int r) {  // 0-indexed
        return sum(r) - sum(l);
    }

    void add(int idx, T x) {  // 0-indexed
        idx++;
        for (int i = idx; i <= n; i += i & -i) dat[i] += x;
    }

    int lower_bound(T x) {
        if (x <= 0) return T(0);
        int res = 0, r = 1;
        while (r < n) r <<= 1;
        for (; r > 0; r >>= 1) {
            if (res + r <= n && dat[res + r] < x) {
                x -= dat[res + r];
                res += r;
            }
        }
        return res + 1;
    }

    void print() {
        for (int i = 0; i < n; i++) cout << sum(i, i + 1) << " ";
        cout << endl;
    }
};

signed main() {
    int n;
    cin >> n;
    HLD hld(n);
    int par[n] = {};
    int k, c;
    rep(i, n) {
        cin >> k;
        rep(j, k) {
            cin >> c;
            hld.add_edge(i, c);
            par[c] = i;
        }
    }
    hld.build();
    BIT<int> bit(n);
    int q;
    cin >> q;
    int Q, u, v, w;
    rep(i, q) {
        cin >> Q;
        if (Q == 0) {
            cin >> v >> w;
            auto f = [&](int a, int b) { return bit.add(a, w); };
            hld.for_each_edge(par[v], v, f);
        } else {
            cin >> u;
            int ans = 0;
            auto f = [&](int a, int b) { ans += bit.sum(a, b); };
            hld.for_each_edge(0, u, f);
            cout << ans << endl;
        }
    }
    return 0;
}