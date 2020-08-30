// ABC-21-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

template <int MOD = 1000000007>
struct Mint {
    int x;

    Mint() : x(0) {}
    Mint(long long t) {
        x = t % MOD;
        if (x < 0) x += MOD;
    }

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
};

// MODint依存
template <typename T>
struct Comb {
    vector<T> fac, fin;

    Comb(int sz) : fac(sz + 1), fin(sz + 1) {
        fac[0] = fin[sz] = T(1);
        for (int i = 1; i <= sz; i++) {
            fac[i] = fac[i - 1] * T(i);
        }
        fin[sz] /= fac[sz];
        for (int i = sz - 1; i >= 0; i--) {
            fin[i] = fin[i + 1] * T(i + 1);
        }
    }

    // 階乗
    inline T fact(int k) const {
        return fac[k];
    }

    inline T finv(int k) const {
        return fin[k];
    }

    // 順列
    T P(int n, int k) const {
        if (k < 0 || n < k) return T(0);
        return fac[n] * fin[n - k];
    }

    // 組み合わせ
    T C(int n, int k) const {
        if (k < 0 || n < k) return T(0);
        return fac[n] * fin[n - k] * fin[k];
    }

    // 重複組み合わせ
    T H(int n, int k) const {
        if (n < 0 || k < 0) return T(0);
        return k == 0 ? T(1) : C(n + k - 1, k);
    }

    // ベル数
    T B(int n, int k) const {
        if (n == 0) return T(1);
        k = min(k, n);
        vector<T> dp(k + 1);
        dp[0] = T(1);
        for (int i = 1; i <= k; i++) {
            if (i & 1)
                dp[i] = dp[i - 1] - fin[i];
            else
                dp[i] = dp[i - 1] + fin[i];
        }
        T res(0);
        for (int i = 1; i <= k; i++) {
            // MODint依存
            res += T(i).pow(n) * fin[i] * dp[k - i];
        }
        return res;
    }

    // スターリング数
    T S(int n, int k) const {
        T res(0);
        for (int i = 1; i <= k; i++) {
            // MODint依存
            T t = C(k, i) * T(i).pow(n);
            if ((k - i) & 1)
                res -= t;
            else
                res += t;
        }
        return res * fin[k];
    }
};

/*
    P(5, 3)の場合 :
    0 + 0 + 5 = 0 + 1 + 4 = 0 + 2 + 3 = 1 + 1 + 3 = 1 + 2 + 2
    よって、P(5, 3) = 5
*/
template <typename T>
struct Partition {
    vector<vector<T>> dp;

    Partition(int sz) : dp(sz + 1, vector<T>(sz + 1)) {
        dp[0][0] = T(1);
        for (int i = 0; i <= sz; i++) {
            for (int j = 1; j <= sz; j++) {
                if (i - j >= 0)
                    dp[i][j] = dp[i][j - 1] + dp[i - j][j];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
    }

    //分割数
    T P(int n, int k) {
        if (n < 0 || k < 0) return T(0);
        return dp[n][k];
    }
};

/*
    MODint依存
    計算量 : O(k)
*/
template <typename T>
T C(long long n, int k) {
    T num(1), denom(1);
    for (int i = 0; i < k; i++) {
        num *= T(n - i);
        denom *= T(i + 1);
    }
    return num / denom;
}

signed main() {
    int n, k;
    cin >> n >> k;
    Comb<Mint<>> C(n + k);
    cout << C.H(n, k) << endl;
    return 0;
}