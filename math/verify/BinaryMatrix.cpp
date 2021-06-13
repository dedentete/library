// typical90-57
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int MOD = 998244353;

/*
    実行時MODint :
    template <int& MOD = 1000000007>
    static int MOD;
    cin >> MOD;
*/
template <int MOD = 1000000007>
struct Mint {
    int x;

    constexpr Mint() : x(0) {}
    constexpr Mint(long long t)
        : x(t >= 0 ? (t % MOD) : (MOD - (-t) % MOD) % MOD) {}

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

// https://github.com/tsutaj/cpp_library/blob/master/math/math_005_matrix_mod2.cpp
struct BinaryMatrix {
    static constexpr int MAX = 2000;

    using mat = vector<bitset<MAX>>;

    int h, w;
    mat A;

    BinaryMatrix(int h, int w) : h(h), w(w), A(h) {}
    BinaryMatrix(mat A) : A(A) {}

    const bitset<MAX> &operator[](int i) const {
        return A[i];
    }

    bitset<MAX> &operator[](int i) {
        return A[i];
    }

    BinaryMatrix T(const BinaryMatrix &A) {
        int h = A.h, w = A.w;
        BinaryMatrix B(w, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                B[j][i] = A[i][j];
            }
        }
        return B;
    }

    BinaryMatrix &operator+=(const BinaryMatrix &B) {
        assert(h == B.h and w == B.w);
        for (int i = 0; i < h; i++) A[i] ^= B[i];
        return *this;
    }

    BinaryMatrix &operator-=(const BinaryMatrix &B) {
        return (*this += B);
    }

    BinaryMatrix &operator*=(const BinaryMatrix &B) {
        assert(w == B.h);
        BinaryMatrix res(h, B.w), C = T(B);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < B.w; j++) {
                res[i][j] = (A[i] & C[j]).count() % 2;
            }
        }
        return (*this = res);
    }

    BinaryMatrix operator+(const BinaryMatrix &B) {
        return (BinaryMatrix(*this) += B);
    }

    BinaryMatrix operator-(const BinaryMatrix &B) {
        return (BinaryMatrix(*this) -= B);
    }

    BinaryMatrix operator*(const BinaryMatrix &B) {
        return (BinaryMatrix(*this) *= B);
    }

    bool operator==(const BinaryMatrix &B) const {
        if (h != B.h or w != B.w) return false;
        for (int i = 0; i < h; i++)
            if (A[i] != B[i]) return false;
        return true;
    }

    bool operator!=(const BinaryMatrix &B) const {
        return !(*this == B);
    }

    BinaryMatrix identity(int n) {
        BinaryMatrix E(n, n);
        for (int i = 0; i < n; i++) E[i][i] = 1;
        return E;
    }

    BinaryMatrix pow(long long n) {
        BinaryMatrix B(A), C = identity(h);
        while (n > 0) {
            if (n & 1) C *= B;
            B *= B;
            n >>= 1;
        }
        return C;
    }

    void gauss(bool augmented = false) {
        int rank = 0;
        for (int i = 0; i < w; i++) {
            int idx = -1;
            for (int j = rank; j < h - augmented; j++) {
                if (A[j][i]) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) {
                continue;
            }
            swap(A[rank], A[idx]);
            for (int j = rank + 1; j < h; j++) {
                if (A[j][i]) {
                    A[j] ^= A[rank];
                }
            }
            rank++;
        }
    }

    // Ax = b
    void equation(vector<int> b) {
        bitset<MAX> bit;
        for (int i = 0; i < w; i++) {
            bit[i] = b[i];
        }
        A.emplace_back(bit);
        h++;
        gauss(true);
    }
};

signed main() {
    int n, m;
    cin >> n >> m;
    BinaryMatrix A(n, m);
    int t, a;
    rep(i, n) {
        cin >> t;
        rep(j, t) {
            cin >> a;
            a--;
            A[i][a] = 1;
        }
    }
    vector<int> s(m);
    rep(i, m) {
        cin >> s[i];
    }
    A.equation(s);
    if (A[n].any()) {
        cout << 0 << endl;
    } else {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (A[i].none()) {
                cnt++;
            }
        }
        cout << Mint<MOD>(2).pow(cnt) << endl;
    }
    return 0;
}