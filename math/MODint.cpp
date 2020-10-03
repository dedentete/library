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