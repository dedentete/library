long long GCD(long long m,long long n){
    if(n == 0) return m;
    else return GCD(n,m % n);
}