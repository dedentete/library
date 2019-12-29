//ABC-57-D
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

template <typename T>
vector<vector<T>> PascalTriangle(int n){
    vector<vector<T>> C(n + 1, vector<T>(n + 1));
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C;
}

signed main(){
    int n,a,b;
    cin >> n >> a >> b;
    ll v[n];
    REP(i,n){
        cin >> v[i];
    }
    sort(v, v + n);
    reverse(v, v + n);
    double maxave = 0.0;
    for(int i = 0; i < a; i++){
        maxave += (double)v[i];
    }
    maxave /= a;
    printf("%.10lf\n", maxave);
    vector<vector<ll>> C = PascalTriangle<ll>(50);
    if(v[0] != v[a - 1]){
        int cntall = 0, cntin = 0;
        for(int i = 0; i < n; i++){
            if(v[i] == v[a - 1]) cntall++;
        }
        for(int i = 0; i < a; i++){
            if(v[i] == v[a - 1]) cntin++;
        }
        cout << C[cntall][cntin] << endl;
    }else{
        int cntall = 0;
        for(int i = 0; i < n; i++){
            if(v[i] == v[0]) cntall++;
        }
        ll ans = 0;
        for(int i = a; i <= min(cntall, b); i++){
            ans += C[cntall][i];
        }
        cout << ans << endl;
    }
    return 0;
}