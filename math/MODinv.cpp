long long MODinv(long long a){//a ÷ b mod. MOD の求め方 : a * modinv(b) % MOD
    long long b = MOD, u = 1, v = 0;
    while(b){
        long long t = a / b;
        a -= t * b;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    u %= MOD;
    if(u < 0) u += MOD;
    return u;
}