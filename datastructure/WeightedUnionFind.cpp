template <typename T>
struct WeightedUnionFind {
    vector<int> par, siz;
    vector<T> ws;

    WeightedUnionFind(int n) : par(n), siz(n, 1), ws(n, T(0)) {
        iota(par.begin(), par.end(), 0);
    }

    int root(int x) {
        if (par[x] == x) return x;
        int t = root(par[x]);
        ws[x] += ws[par[x]];
        return par[x] = t;
    }

    T weight(int x) {
        root(x);
        return ws[x];
    }

    void unite(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);
        x = root(x);
        y = root(y);
        if (x == y) return;
        if (siz[x] < siz[y]) {
            swap(x, y);
            w = -w;
        }
        siz[x] += siz[y];
        par[y] = x;
        ws[y] = w;
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    int size(int x) {
        return siz[root(x)];
    }

    T diff(int x, int y) {
        return weight(y) - weight(x);
    }
};