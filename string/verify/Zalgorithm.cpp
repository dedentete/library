//ABC-141-E
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i = 0; i < (n); i++)
#define ALL(v) (v).begin(),(v).end()
using ll = long long;
using P = pair<int, int>;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;
const long long B = 1007;

template<typename T>
vector<int> Zalgorithm(const vector<T> & v){
    int n = v.size();
    vector<int> res(n);
    res[0] = n;
    int i = 1, j = 0;
    while(i < n){
        while(i + j < n && v[j] == v[i + j]) j++;
        res[i] = j;
        if(j == 0){
            i++;
            continue;
        }
        int k = 1;
        while(i + k < n && k + res[k] < j){
            res[i + k] = res[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return res;
}

vector<int> Zalgorithm(const string & s){
    return Zalgorithm(vector<char>(s.begin(), s.end()));
}

signed main(){
    int n;
    string s;
    cin >> n;
    cin >> s;
    int ans = 0;
    rep(i,n){
        vector<int> z = Zalgorithm(s.substr(i));
        rep(j,z.size()){
            if(z[j] <= j){
                ans = max(ans, z[j]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}