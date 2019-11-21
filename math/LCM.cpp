long long LCM(long long m, long long n){
    long long g = GCD(m, n);
    return m / g * n;
}