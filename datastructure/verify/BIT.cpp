// ARC033 C
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

template <typename T>
struct BIT {
    int n;
    vector<T> dat;

    BIT(int n) : n(n), dat(n + 1, 0) {}

    T sum(int idx) {  // 1-indexed
        T res(0);
        for (int i = idx; i > 0; i -= i & -i) res += dat[i];
        return res;
    }

    T sum(int l, int r) {  // 0-indexed
        return sum(r) - sum(l);
    }

    void add(int idx, T x) {  // 0-indexed
        idx++;
        for (int i = idx; i <= n; i += i & -i) dat[i] += x;
    }

    int lower_bound(T x) {
        if (x <= 0) return T(0);
        int res = 0, r = 1;
        while (r < n) r <<= 1;
        for (; r > 0; r >>= 1) {
            if (res + r <= n && dat[res + r] < x) {
                x -= dat[res + r];
                res += r;
            }
        }
        return res;
    }

    void print() {
        for (int i = 0; i < n; i++) cout << sum(i, i + 1) << " ";
        cout << endl;
    }
};

signed main() {
    int q;
    cin >> q;
    BIT<int> bit((int)2e5 + 1);
    int t, x;
    rep(i, q) {
        cin >> t >> x;
        if (t == 1) {
            bit.add(x, 1);
        } else {
            int t = bit.lower_bound(x);
            cout << t << endl;
            bit.add(t, -1);
        }
    }
    return 0;
}