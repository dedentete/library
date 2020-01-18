//ABC-87-B
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
struct WeightedUnionFind{
    vector<int> par,siz;
    vector<T> ws;

    WeightedUnionFind(int n) : par(n), siz(n, 1), ws(n, T(0)){
        iota(par.begin(), par.end(), 0);
    }

    int root(int x){
        if(par[x] == x) return x;
        int t = root(par[x]);
        ws[x] += ws[par[x]];
        return par[x] = t;
    }

    T weight(int x){
        root(x);
        return ws[x];
    }

    void unite(int x, int y, T w){
        w += weight(x);
        w -= weight(y);
        x = root(x);
        y = root(y);
        if(x == y) return;
        if(siz[x] < siz[y]){
            swap(x, y);
            w = -w;
        }
        siz[x] += siz[y];
        par[y] = x;
        ws[y] = w;
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }

    int size(int x){
        return siz[root(x)];
    }

    T diff(int x, int y){
        return weight(y) - weight(x);
    }
};

signed main(){
    int n,m;
    cin >> n >> m;
    int l[m],r[m],d[m];
    REP(i,m){
        cin >> l[i] >> r[i] >> d[i];
        l[i]--;
        r[i]--;
    }
    WeightedUnionFind<ll> wuf(n);
    for(int i = 0; i < m; i++){
        if(wuf.same(l[i], r[i]) && wuf.diff(l[i], r[i]) != d[i]){
            cout << "No" << endl;
            return 0;
        }
        wuf.unite(l[i], r[i], d[i]);
    }
    cout << "Yes" << endl;
    return 0;
}