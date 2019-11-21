map<long long, int> PrimeFactor(long long n){
    map<long long, int> mp;
    for(int i = 2; (long long)i * i <= n; i++){
        while(n % i == 0){
            mp[i]++;
            n /= i;
        }
    }
    if(n != 1) mp[n]++;
    return mp;
}