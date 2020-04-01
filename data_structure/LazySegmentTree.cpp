/*
    LazySegmentTree<ll, ll> seg(f, g, h, p, def, laz_def) のように宣言する
    RMQ and RUQ の場合 :
    auto f = [](ll a, ll b){return min(a, b);};
    auto g = [](ll a, ll b){return b;};
    auto h = [](ll a, ll b){return b;};
    auto p = [](ll a, ll b){return a;};
    RSQ and RAQ の場合 :
    auto f = [](ll a, ll b){return a + b;};
    auto g = [](ll a, ll b){return a + b;};
    auto h = [](ll a, ll b){return a + b;};
    auto p = [](ll a, int b){return a * b;};
*/
template <typename Monoid, typename OperatorMonoid>
struct LazySegmentTree {
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid, OperatorMonoid)>;
    using H = function<OperatorMonoid(OperatorMonoid, OperatorMonoid)>;
    using P = function<OperatorMonoid(OperatorMonoid, int)>;
    int n;
    vector<Monoid> dat;
    vector<OperatorMonoid> laz;
    F f;
    G g;
    H h;
    P p;
    Monoid def;
    OperatorMonoid laz_def;

    LazySegmentTree(F f, G g, H h, P p, Monoid def, OperatorMonoid laz_def)
        : f(f), g(g), h(h), p(p), def(def), laz_def(laz_def) {}

    void build(const vector<Monoid>& vec) {
        int siz = vec.size();
        n = 1;
        while (n < siz) n *= 2;
        dat.assign(2 * n - 1, def);
        laz.assign(2 * n - 1, laz_def);
        for (int i = 0; i < siz; i++) dat[n - 1 + i] = vec[i];
        for (int i = n - 2; i >= 0; i--)
            dat[i] = f(dat[2 * i + 1], dat[2 * i + 2]);
    }

    void update(int a, int b, OperatorMonoid x) {
        update(a, b, x, 0, 0, n);
    }

    Monoid query(int a, int b) {
        return query(a, b, 0, 0, n);
    }

   private:
    void eval(int k, int l, int r) {
        if (laz[k] != laz_def) {
            dat[k] = g(dat[k], p(laz[k], r - l));
            if (r - l > 1) {
                laz[2 * k + 1] = h(laz[2 * k + 1], laz[k]);
                laz[2 * k + 2] = h(laz[2 * k + 2], laz[k]);
            }
            laz[k] = laz_def;
        }
    }

    void update(int a, int b, OperatorMonoid x, int k, int l, int r) {
        eval(k, l, r);
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            laz[k] = h(laz[k], x);
            eval(k, l, r);
        } else {
            update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update(a, b, x, 2 * k + 2, (l + r) / 2, r);
            dat[k] = f(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    Monoid query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return def;
        eval(k, l, r);
        if (a <= l && r <= b) return dat[k];
        Monoid vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        Monoid vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
};