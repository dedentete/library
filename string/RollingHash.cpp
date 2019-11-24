/*
    基数として乱数をとりたい場合 : 
    ll MOD_1 = 1000000007, MOD_2 = 1000000009;
    random_device rnd;
    mt19937 mt(rnd());
    B_1 = mt() % (MOD_1 - 2) + 2;
    B_2 = mt() % (MOD_2 - 2) + 2;
    RolligHash rh(s, B_1, B_2, MOD_1, MOD_2);
*/
struct RollingHash{
    using T = long long;
    using P = pair<T, T>;
    T B_1, B_2, MOD_1, MOD_2;
    vector<T> hash_1, hash_2, pow_1, pow_2;
    
    RollingHash(string & s, T B_1 = 1007, T B_2 = 1009, T MOD_1 = 1000000007, T MOD_2 = 1000000009)
     : B_1(B_1), B_2(B_2), MOD_1(MOD_1), MOD_2(MOD_2) {
        int n = s.size();
        hash_1.assign(n + 1, 0);
        hash_2.assign(n + 1, 0);
        pow_1.assign(n + 1, 1);
        pow_2.assign(n + 1, 1);
        for(int i = 0; i < n; i++){
            hash_1[i + 1] = (hash_1[i] * B_1 + s[i]) % MOD_1;
            hash_2[i + 1] = (hash_2[i] * B_2 + s[i]) % MOD_2;
            pow_1[i + 1] = pow_1[i] * B_1 % MOD_1;
            pow_2[i + 1] = pow_2[i] * B_2 % MOD_2;
        }
    }

    P get(int l, int r){
        T res_1 = ((hash_1[r] - hash_1[l] * pow_1[r - l]) % MOD_1 + MOD_1) % MOD_1;
        T res_2 = ((hash_2[r] - hash_2[l] * pow_2[r - l]) % MOD_2 + MOD_2) % MOD_2;
        return P(res_1, res_2);
    }
};