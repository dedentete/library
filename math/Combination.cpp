template <typename T>
struct Comb{
    vector<T> fact, finv;

    Comb(int sz) : fact(sz + 1), fin(sz + 1){
        fact[0] = finv[sz] = T(1);
        for(int i = 1; i <= sz; i++){
            fact[i] = fact[i - 1] * T(i);
        }
        finv[sz] /= fact[sz];
        for(int i = sz - 1; i >= 0; i--){
            finv[i] = finv[i + 1] * T(i + 1);
        }
    }

    inline T fact(int k) const { return fact[k]; }
    inline T finv(int k) const { return finv[k]; }

    T P(int n, int k) const {
        if(k < 0 || n < k) return T(0);
        return fact[n] * finv[n - k];
    }

    T C(int n, int k) const {
        if(k < 0 || n < k) return T(0);
        return fact[n] * finv[n - k] * finv[k];
    }

    T H(int n, int k) const {
        if(n < 0 || k < 0) return T(0);
        return k == 0 ? T(1) : C(n + k - 1, k);
    }
};