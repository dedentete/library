// EDPC-Z
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
using P = pair<int, int>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

/*
    追加クエリの傾き a が単調の場合しか使えない (単調でない場合はLi Chao
   Treeを使う)
*/
template <typename T, bool isMin>
struct CHT {
#define F first
#define S second
    using P = pair<T, T>;
    deque<P> H;

    bool empty() const {
        return H.empty();
    }

    void clear() {
        H.clear();
    }

    inline int sgn(T x) {
        return x == 0 ? 0 : (x < 0 ? -1 : 1);
    }

    inline bool check(const P& a, const P& b, const P& c) {
        if (b.S == a.S || c.S == b.S)
            return sgn(b.F - a.F) * sgn(c.S - b.S) >=
                   sgn(c.F - b.F) * sgn(b.S - a.S);
        return (long double)(b.F - a.F) * sgn(c.S - b.S) /
                   (long double)(abs(b.S - a.S)) >=
               (long double)(c.F - b.F) * sgn(b.S - a.S) /
                   (long double)(abs(c.S - b.S));
    }

    void add(T a, T b) {
        if (!isMin) a *= -1, b *= -1;
        P line(a, b);
        if (empty()) {
            H.emplace_front(line);
            return;
        }
        if (H.front().F <= a) {
            if (H.front().F == a) {
                if (H.front().S <= b) return;
                H.pop_front();
            }
            while (H.size() > 1 && check(line, H.front(), H[1])) H.pop_front();
            H.emplace_front(line);
        } else {
            assert(a <= H.back().F);
            if (H.back().F == a) {
                if (H.back().S <= b) return;
                H.pop_back();
            }
            while (H.size() > 1 && check(H[H.size() - 2], H.back(), line))
                H.pop_back();
            H.emplace_back(line);
        }
    }

    inline T getY(const P& a, const T& x) {
        return a.F * x + a.S;
    }

    T query(T x) {
        assert(!empty());
        int l = -1, r = H.size() - 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (getY(H[m], x) >= getY(H[m + 1], x))
                l = m;
            else
                r = m;
        }
        if (isMin) return getY(H[r], x);
        return -getY(H[r], x);
    }
};

signed main() {
    int n;
    ll c;
    cin >> n >> c;
    ll h[n];
    rep(i, n) {
        cin >> h[i];
    }
    CHT<ll, true> cht;
    ll dp[n];
    dp[0] = 0;
    rep(i, n) {
        if (i) dp[i] = cht.query(h[i]) + h[i] * h[i];
        cht.add(-2 * h[i], h[i] * h[i] + dp[i] + c);
    }
    cout << dp[n - 1] << endl;
    return 0;
}