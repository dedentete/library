struct UnionFind{
    vector<int> par,siz;

    UnionFind(int n) : par(n), siz(n, 1){
        iota(par.begin(), par.end(), 0);
    }

    int root(int x){
        if(par[x] == x) return x;
        else return par[x] = root(par[x]);
    }

    void unite(int x, int y){
        x = root(x);
        y = root(y);
        if(x == y) return;
        if(siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        par[y] = x;
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }

    int size(int x){
        return siz[root(x)];
    }
};