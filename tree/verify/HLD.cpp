// PAST202010-M
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

// https://beet-aizu.github.io/library/segtree/basic/dual.cpp
template <typename E>
struct DualSegmentTree {
    using H = function<E(E, E)>;
    int n, height;
    H h;
    E ei;
    vector<E> laz;

    DualSegmentTree(H h, E ei) : h(h), ei(ei) {}

    void init(int n_) {
        n = 1;
        height = 0;
        while (n < n_) n <<= 1, height++;
        laz.assign(2 * n, ei);
    }

    inline void propagate(int k) {
        if (laz[k] == ei) return;
        laz[(k << 1) | 0] = h(laz[(k << 1) | 0], laz[k]);
        laz[(k << 1) | 1] = h(laz[(k << 1) | 1], laz[k]);
        laz[k] = ei;
    }

    inline void thrust(int k) {
        for (int i = height; i; i--) propagate(k >> i);
    }

    void update(int a, int b, E x) {
        if (a >= b) return;
        thrust(a += n);
        thrust(b += n - 1);
        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) laz[l] = h(laz[l], x), l++;
            if (r & 1) --r, laz[r] = h(laz[r], x);
        }
    }

    void update(int a, E x) {
        thrust(a += n);
        laz[a] = x;
    }

    E get(int a) {
        thrust(a += n);
        return laz[a];
    }
};

signed main() {
    int n, q;
    cin >> n >> q;
    HLD hld(n);
    pair<int, int> ap[n - 1];
    int a, b;
    rep(i, n - 1) {
        cin >> a >> b;
        a--;
        b--;
        hld.add_edge(a, b);
        ap[i] = {a, b};
    }
    hld.build();
    auto h = [](int a, int b) { return b; };
    int ei = -1;
    DualSegmentTree<int> seg(h, ei);
    seg.init(n);
    seg.update(0, n, 0);
    int u, v, c;
    rep(i, q) {
        cin >> u >> v >> c;
        u--;
        v--;
        auto ff = [&](int a, int b) { return seg.update(a, b, c); };
        hld.for_each_edge(u, v, ff);
    }
    int ans;
    auto ff = [&](int a, int b) { ans = seg.get(a); };
    for (auto p : ap) {
        hld.for_each_edge(p.first, p.second, ff);
        cout << ans << endl;
    }
    return 0;
}