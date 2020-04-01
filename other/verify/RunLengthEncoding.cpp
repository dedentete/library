// ARC-44-B
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a) for (int i = 0; i < (a); i++)
#define ALL(a) (a).begin(), (a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

using ll = long long;
template <ll MOD = 1000000007>
struct Mint {
    ll x;

    Mint() : x(0) {}
    Mint(ll t) {
        x = t % MOD;
        if (x < 0) x += MOD;
    }

    Mint pow(ll n) {
        Mint res(1), t(x);
        while (n > 0) {
            if (n & 1) res *= t;
            t *= t;
            n >>= 1;
        }
        return res;
    }

    Mint inv() const {
        ll a = x, b = MOD, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        return Mint(u);
    }

    Mint &operator+=(Mint a) {
        x += a.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }

    Mint &operator-=(Mint a) {
        x += MOD - a.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }

    Mint &operator*=(Mint a) {
        x = 1LL * x * a.x % MOD;
        return *this;
    }

    Mint &operator/=(Mint a) {
        return (*this) *= a.inv();
    }

    Mint operator+(Mint a) const {
        return Mint(x) += a;
    }
    Mint operator-(Mint a) const {
        return Mint(x) -= a;
    }
    Mint operator*(Mint a) const {
        return Mint(x) *= a;
    }
    Mint operator/(Mint a) const {
        return Mint(x) /= a;
    }

    Mint operator-() const {
        return Mint(-x);
    }

    bool operator==(const Mint a) {
        return x == a.x;
    }
    bool operator!=(const Mint a) {
        return x != a.x;
    }
    bool operator<(const Mint a) {
        return x < a.x;
    }

    friend ostream &operator<<(ostream &os, const Mint &a) {
        return os << a.x;
    }

    friend istream &operator>>(istream &is, Mint &a) {
        ll t;
        is >> t;
        a = Mint<MOD>(t);
        return (is);
    }
};

template <typename T>
vector<pair<int, T>> RLE(vector<T> v) {
    int n = v.size();
    vector<pair<int, T>> res;
    T pre = v[0];
    int cnt = 1;
    for (int i = 1; i < n; i++) {
        if (v[i] != pre) {
            res.emplace_back(cnt, pre);
            pre = v[i];
            cnt = 0;
        }
        cnt++;
    }
    res.emplace_back(cnt, pre);
    return res;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    REP(i, n) {
        cin >> a[i];
    }
    if (a[0] != 0) {
        cout << 0 << endl;
        return 0;
    }
    sort(ALL(a));
    if (n > 1 && a[1] == 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<pair<int, int>> r = RLE(a);
    int k = r.size();
    for (int i = 0; i < k - 1; i++) {
        if (r[i].second + 1 != r[i + 1].second) {
            cout << 0 << endl;
            return 0;
        }
    }
    Mint<> ans = 1;
    for (int i = 0; i < k - 1; i++) {
        ans *= (Mint<>(2).pow(r[i].first) - Mint<>(1)).pow(r[i + 1].first);
        ans *=
            Mint<>(2).pow((ll)r[i + 1].first * (ll)(r[i + 1].first - 1) / 2LL);
    }
    cout << ans << endl;
    return 0;
}