//ABC-12-D
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

/*
    辺が存在しない場合、dist[i][j] = INF、ただしdist[i][i] = 0 とする
    頂点数 V のとき : 
    vector<vector<int>> dist(V, vector<int>(V, INF));
    for(int i = 0; i < V; i++){
        dist[i][i] = 0;
    }
*/
template <typename T>
void Warshall_Floyd(vector<vector<T>> & dist){
    int V = dist.size();
    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    // dist[i][i] < 0 が存在 <-> 負の閉路が存在
}

signed main(){
	int n,m;
	cin >> n >> m;
	int a,b,t;
	vector<vector<int>> dist(n, vector<int>(n, INF));
	for(int i = 0; i < n; i++){
		dist[i][i] = 0;
	}
	REP(i,m){
		cin >> a >> b >> t;
		a--;
		b--;
		dist[a][b] = dist[b][a] = t;
	}
	Warshall_Floyd(dist);
	int mn = INF;
	for(int i = 0; i < n; i++){
		int mx = 0;
		for(int j = 0; j < n; j++){
			mx = max(mx, dist[i][j]);
		}
		mn = min(mn, mx);
	}
	cout << mn << endl;
	return 0;
}