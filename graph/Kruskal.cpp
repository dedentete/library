struct UnionFind {
    vector<int> par;
    vector<int> siz;

    UnionFind(int n) : par(n), siz(n, 1) {
        iota(par.begin(), par.end(), 0);
    }

    int root(int x) {
        if (par[x] == x)
            return x;
        else
            return par[x] = root(par[x]);
    }

    void unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return;
        if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        par[y] = x;
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    int size(int x) {
        return siz[root(x)];
    }
};

template <typename T>
struct edge {
    int from, to;
    T cost;
    edge(int from, int to, T cost = 1) : from(from), to(to), cost(cost) {}
    bool operator<(const edge& e) const {
        return cost < e.cost;
    }
};

template <typename T>
T Kruskal(int V, vector<edge<T>>& es) {
    sort(es.begin(), es.end());  // reverseすると最大全域木
    UnionFind uf(V);
    T res = 0;
    for (edge<T> e : es) {
        if (!uf.same(e.from, e.to)) {
            uf.unite(e.from, e.to);
            res += e.cost;
        }
    }
    return res;
}