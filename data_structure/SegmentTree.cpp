/*
    SegmentTree<int> seg(f, def) のように宣言する
    RMQ の場合 : 
    auto f = [](int a, int b){return min(a, b);};
    int def = INF;
*/
template <typename Monoid>
struct SegmentTree{
    using F = function<Monoid(Monoid, Monoid)>;
    int n;
    vector<Monoid> dat;
    F f;
    Monoid def;

    SegmentTree(F f, Monoid def) : f(f), def(def) {}

    void build(const vector<Monoid> & vec){
        int siz = vec.size();
        n = 1;
        while(n < siz) n *= 2;
        dat.assign(2 * n - 1, def);
        for(int i = 0; i < siz; i++) dat[n - 1 + i] = vec[i];
        for(int i = n - 2; i >= 0; i--) dat[i] = f(dat[2 * i + 1], dat[2 * i + 2]);
    }

    void update(int k, Monoid x){
        k += (n - 1);
        dat[k] = x;
        while(k > 0){
            k = (k - 1) / 2;
            dat[k] = f(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    Monoid query(int a, int b){
        return query(a, b, 0, 0, n);
    }

private:
    Monoid query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return def;
        if(a <= l && r <= b) return dat[k];
        Monoid vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        Monoid vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
};