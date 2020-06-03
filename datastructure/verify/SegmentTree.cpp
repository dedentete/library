// AOJ-DSL-2-A
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a) for (int i = 0; i < (a); i++)
#define ALL(a) (a).begin(), (a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

/*
    SegmentTree<int> seg(f, def) のように宣言する
    RMQ の場合 :
    auto f = [](int a, int b){return min(a, b);};
    int def = INF;
*/
template <typename Monoid>
struct SegmentTree {
    using F = function<Monoid(Monoid, Monoid)>;
    int n;
    vector<Monoid> dat;
    F f;
    Monoid def;

    SegmentTree(F f, Monoid def) : f(f), def(def) {}

    void build(const vector<Monoid>& vec) {
        int sz = vec.size();
        n = 1;
        while (n < sz) n *= 2;
        dat.assign(2 * n - 1, def);
        for (int i = 0; i < sz; i++) dat[n - 1 + i] = vec[i];
        for (int i = n - 2; i >= 0; i--)
            dat[i] = f(dat[2 * i + 1], dat[2 * i + 2]);
    }

    void update(int k, Monoid x) {
        k += (n - 1);
        dat[k] = x;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = f(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }

    Monoid query(int a, int b) {
        return query(a, b, 0, 0, n);
    }

   private:
    Monoid query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return def;
        if (a <= l && r <= b) return dat[k];
        Monoid vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        Monoid vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
};

signed main() {
    int n, q;
    cin >> n >> q;
    auto f = [](int a, int b) { return min(a, b); };
    SegmentTree<int> seg(f, INT_MAX);
    seg.build(vector<int>(n, INT_MAX));
    int c, x, y;
    REP(i, q) {
        cin >> c >> x >> y;
        if (c == 0) {
            seg.update(x, y);
        } else {
            cout << seg.query(x, y + 1) << endl;
        }
    }
    return 0;
}