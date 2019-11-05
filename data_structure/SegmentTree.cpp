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
    Monoid def; //初期値かつ単位元

    SegmentTree(F f, Monoid def) : f(f), def(def) {}

    void build(const vector<Monoid> & vec){ //元配列vecをセグメントツリーで表現する
        int siz = vec.size();
        n = 1;
        while(n < siz) n *= 2;
        dat.assign(2 * n - 1, def);
        for(int i = 0; i < siz; i++) dat[n - 1 + i] = vec[i]; //最下段に値をいれる
        for(int i = n - 2; i >= 0; i--) dat[i] = f(dat[2 * i + 1], dat[2 * i + 2]); //下の段から順番に値をいれる
    }

    void update(int k, Monoid x){
        k += (n - 1); //最下段のノードにアクセスする
        dat[k] = x; //最下段のノードを更新したら、下の段から順番に値をいれる
        while(k > 0){
            k = (k - 1) / 2;
            dat[k] = f(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    //[a, b)の区間クエリを実行
    Monoid query(int a, int b){
        return query(a, b, 0, 0, n);
    }

private:
    Monoid query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return def; //要求区間と対象区間が交わらなければ、def
        if(a <= l && r <= b) return dat[k]; //要求区間が対象区間を完全に含んでいれば、対象区間を答えの計算に使う
        //要求区間が対象区間の一部を含んでいれば、
        Monoid vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        Monoid vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
};