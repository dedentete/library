//yukicoder-430
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<ll, ll> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

/*
    基数として乱数をとりたい場合、コメントアウトをはずす
*/
struct RollingHash{
    using T = long long;
    using P = pair<T, T>;
    T B_1, B_2, MOD_1, MOD_2;
    vector<T> hash_1, hash_2, pow_1, pow_2;
    
    RollingHash(string & s, T B_1 = 1007, T B_2 = 1009, T MOD_1 = 1000000007, T MOD_2 = 1000000009)
     : B_1(B_1), B_2(B_2), MOD_1(MOD_1), MOD_2(MOD_2) {
        int n = s.size();
        /*
        random_device rnd;
        mt19937 mt(rnd());
        B_1 = mt() % (MOD_1 - 2) + 2;
        B_2 = mt() % (MOD_2 - 2) + 2;
        */    
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

signed main(){
    string s;
    cin >> s;
    int n = s.size();
    int m;
    cin >> m;
    string c[m];
    REP(i,m){
        cin >> c[i];
    }
    RollingHash rhs(s);
    vector<map<P, int>> mp(11);
    for(int i = 1; i <= 10; i++){
        for(int j = 0; j + i <= n; j++){
            mp[i][rhs.get(j, j + i)]++;
        }
    }
    int ans = 0;
    REP(i,m){
        RollingHash rhc(c[i]);
        ans += mp[c[i].size()][rhc.get(0, c[i].size())];
    }
    cout << ans << endl;
    return 0;
}