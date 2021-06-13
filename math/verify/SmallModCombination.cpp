// ARC117-C
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int MOD = 1000000007;

/*
    実行時Modint :
    template <int& MOD = 1000000007>
    static int MOD;
    cin >> MOD;
*/
template <int MOD = 1000000007>
struct Mint {
    int x;

    Mint() : x(0) {}
    Mint(long long t) : x(t >= 0 ? (t % MOD) : (MOD - (-t) % MOD) % MOD) {}

    Mint pow(int n) {
        Mint res(1), t(x);
        while (n > 0) {
            if (n & 1) res *= t;
            t *= t;
            n >>= 1;
        }
        return res;
    }

    Mint inv() const {
        int a = x, b = MOD, u = 1, v = 0, t;
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
        x = int(1LL * x * a.x % MOD);
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
        int t;
        is >> t;
        a = Mint<MOD>(t);
        return (is);
    }

    int mod() {
        return MOD;
    }
};

/*
    MODint依存
    nCk mod p (p < n)
*/
template <typename T>
struct SmallModCombination {
    vector<int> f;
    vector<T> g;

    SmallModCombination(int sz) : f(sz + 1), g(sz + 1) {
        for (int i = 1; i <= sz; i++) {
            int pos = i;
            while (pos % g[0].mod() == 0) {
                pos /= g[0].mod();
                f[i]++;
            }
            g[i] = T(pos);
        }
        g[0] = T(1);
        for (int i = 1; i <= sz; i++) f[i] += f[i - 1];
        for (int i = 1; i <= sz; i++) g[i] *= g[i - 1];
    }

    T C(int n, int k) {
        if (f[n] > f[k] + f[n - k])
            return T(0);
        else
            return g[n] / (g[k] * g[n - k]);
    }
};

signed main() {
    int n;
    cin >> n;
    string c;
    cin >> c;
    map<char, Mint<3>> mp;
    mp['B'] = 0;
    mp['W'] = 1;
    mp['R'] = 2;
    SmallModCombination<Mint<3>> C(400000);
    Mint<3> ans = 0;
    rep(i, n) {
        ans += C.C(n - 1, i) * mp[c[i]];
    }
    if (n % 2 == 0) ans *= Mint<3>(-1);
    if (ans == Mint<3>(0)) {
        cout << "B" << endl;
    } else if (ans == Mint<3>(1)) {
        cout << "W" << endl;
    } else {
        cout << "R" << endl;
    }
    return 0;
}