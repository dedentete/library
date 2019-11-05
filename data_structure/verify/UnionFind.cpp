//ATC001-B
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct UnionFind{
    vector<int> par;
    vector<int> siz;

    UnionFind(int n){
        init(n);
    }

    //n要素で初期化
    void init(int n){
        par.resize(n);
        siz.resize(n);
        for(int i = 0; i < n; i++){
            par[i] = i;
            siz[i] = 1;
        }
    }

    //木の根を求める
    int root(int x){
        if(par[x] == x) return x;
        else return par[x] = root(par[x]);
    }

    //xとyの属する集合を併合
    void unite(int x, int y){
        x = root(x);
        y = root(y);
        if(x == y) return;
        if(siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        par[y] = x;
    }

    bool same(int x, int y){
        return root(x) == root(y);
    }

    int size(int x){
        return siz[root(x)];
    }
};

signed main(){
    int n,q;
    cin >> n >> q;
    UnionFind uf(n);
    int p,a,b;
    REP(i,q){
        cin >> p >> a >> b;
        if(p == 0){
            uf.unite(a, b);
        }else{
            if(uf.same(a,b)){
                cout << "Yes" << endl;
            }else{
                cout << "No" << endl;
            }
        }
    }
    return 0;
}