//EDPC-R
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

using ll = long long;
template <ll MOD = 1000000007>
struct Mint{
    ll x;

    Mint() : x(0) {}
    Mint(ll t){
        x = t % MOD;
        if(x < 0) x += MOD;
    }
    
    Mint pow(ll n){
        Mint res(1), t(x);
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
        x += a.x;
        if(x >= MOD) x -= MOD;
        return *this;
    }
    
    Mint & operator -= (Mint a){
        x += MOD - a.x;
        if(x >= MOD) x -= MOD;
        return *this;
    }

    Mint & operator *= (Mint a){
        x = 1LL * x * a.x % MOD;
        return *this;
    }

    Mint & operator /= (Mint a){
        return (*this) *= a.inv();
    }

    Mint operator + (Mint a) const { return Mint(x) += a; }
    Mint operator - (Mint a) const { return Mint(x) -= a; }
    Mint operator * (Mint a) const { return Mint(x) *= a; }
    Mint operator / (Mint a) const { return Mint(x) /= a; }

    Mint operator - () const{ return Mint(-x); }

    bool operator == (const Mint a){ return x == a.x; }
    bool operator != (const Mint a){ return x != a.x; }
    bool operator < (const Mint a){ return x < a.x; }

    friend ostream & operator << (ostream & os, const Mint &a){
        return os << a.x;
    }

    friend istream & operator >> (istream & is, Mint &a){
        ll t;
        is >> t;
        a = Mint<MOD>(t);
        return (is);
    }
};

/*
    計算量...
    和, 差 : O(N ^ 2)
    積 : O(N ^ 3)
    行列累乗(N ^ K) : O(N ^ 3 log K)
*/
template <typename T>
struct Matrix{
    typedef vector<vector<T>> mat;

    mat A;

    Matrix() {}
    Matrix(int h, int w, T x = T(0)) : A(h, vector<T>(w, x)) {}
    Matrix(mat A) : A(A) {}

    int size() const { return A.size(); }
    const vector<T> & operator[] (int i) const { return A[i]; }
    vector<T> & operator[] (int i) { return A[i]; }

    Matrix & operator += (const Matrix & B){
        assert(A.size() == B.size());
        assert(A[0].size() == B[0].size());
        for(int i = 0; i < A.size(); i++){
            for(int j = 0; j < A[0].size(); j++){
                A[i][j] += B[i][j];
            }
        }
        return *this;
    }

    Matrix & operator -= (const Matrix & B){
        assert(A.size() == B.size());
        assert(A[0].size() == B[0].size());
        for(int i = 0; i < A.size(); i++){
            for(int j = 0; j < A[0].size(); j++){
                A[i][j] -= B[i][j];
            }
        }
        return *this;
    }

    Matrix & operator *= (const Matrix & B){
        assert(A[0].size() == B.size());
        int h = A.size(), w = B[0].size();
        Matrix C(h, w);
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                for(int k = 0; k < B.size(); k++){
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        this->A = C.A;
        return *this;
    }

    Matrix operator + (const Matrix & B) const { return (Matrix(*this) += B); }
    Matrix operator - (const Matrix & B) const { return (Matrix(*this) -= B); }
    Matrix operator * (const Matrix & B) const { return (Matrix(*this) *= B); }

    Matrix identity(int n){
        Matrix E(n, n);
        for(int i = 0; i < n; i++) E[i][i] = T(1);
        return E;
    }

    Matrix pow(long long n){
        Matrix B(A), C = identity(A.size());
        while(n > 0){
            if(n & 1) C *= B;
            B *= B;
            n >>= 1;
        }
        return C;
    }
};

signed main(){
    int n;
    ll k;
    cin >> n >> k;
    Matrix<Mint<>> A(n, n);
    REP(i,n){
        REP(j,n){
            cin >> A[i][j];
        }
    }
    Mint<> ans;
    A = A.pow(k);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ans += A[i][j];
        }
    }
    cout << ans << endl;
    return 0;
}