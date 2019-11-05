struct UnionFind{
    vector<int> par;
    vector<int> siz;

    UnionFind(int n){
        init(n);
    }
    
    void init(int n){
        par.resize(n);
        siz.resize(n);
        for(int i = 0; i < n; i++){
            par[i] = i;
            siz[i] = 1;
        }
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