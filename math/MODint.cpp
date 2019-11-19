using ll = long long;
template <ll MOD = 1000000007>
struct Mint{
    ll v;

    Mint() : v(0) {}
    Mint(ll t){
        v = t % MOD;
        if(v < 0) v += MOD;
    }
    
    Mint pow(ll n){
        Mint res(1), t(v);
        while(n > 0){
            if(n & 1) res *= t;
            t *= t;
            n >>= 1;
        }
        return res;
    }

    Mint inv() const {
        ll a = x, b = MOD, u = 1, v = 0, t;
        while(b > 0){
            t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        return Mint(u);
    }

    Mint & operator += (Mint a){
        v += a.v;
        if(v >= MOD) v -= MOD;
        return *this;
    }
    Mint & operator -= (Mint a){
        v += MOD - a.v;
        if(v >= MOD) v -= MOD;
        return *this;
    }
    Mint & operator *= (Mint a){
        v = 1LL * v * a.v % MOD;
        return *this;
    }
    Mint & operator /= (Mint a){
        return (*this) *= a.inv();
    }

    Mint operator + (Mint a) const { return Mint(v) += a; }
    Mint operator - (Mint a) const { return Mint(v) -= a; }
    Mint operator * (Mint a) const { return Mint(v) *= a; }
    Mint operator / (Mint a) const { return Mint(v) /= a; }

    Mint operator - () const{ return Mint(-v); }

    bool operator == (const Mint a){ return v == a.v; }
    bool operator != (const Mint a){ return v != a.v; }
    bool operator < (const Mint){ return v < a.v; }

    friend ostream & operator << (ostream & os, const Mint &a){
        return os << a.v;
    }

    friend istream & operator >> (istream & is, Mint &a){
        ll t;
        is >> t;
        a = Mint<MOD>(t);
        return (is);
    }
};