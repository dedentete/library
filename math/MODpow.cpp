template <typename T>
T MODpow(T x, T n, T MOD = 1000000007){
    T res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}