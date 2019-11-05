bool is_prime[MAX_L];
bool is_prime_small[MAX_SQRT_B];

//[a,b)の整数に対して篩を行う。is_prime[i - a] = true ⇔ iが素数
void SegmentEratos(long long a, long long b){
    for(int i = 0; (long long)i * i < b; i++) is_prime_small[i] = true;
    for(int i = 0; i < b - a; i++) is_prime[i] = true;

    for(int i = 2; (long long)i * i < b; i++){
        if(is_prime_small[i]){
            for(int j = 2 * i; (long long)j * j < b; j += i) is_prime_small[j] = false;
            for(long long j = max(2LL, (a + i - 1) / i) * i; j < b; j += i) is_prime[j - a] = false;
        }
    }
}