//GigaCode2019-D
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
struct RectangleSum{
    vector<vector<T>> sum;

    RectangleSum(int h, int w){
        init(h, w);
    }

    void init(int h, int w){
        sum.resize(h + 1, vector<T> (w + 1, 0));
    }

    void add(int y, int x, T val){
        y++;
        x++;
        sum[y][x] += val;
    }

    void build(){
        for(int i = 1; i < sum.size(); i++){
            for(int j = 1; j < sum[i].size(); j++){
                sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
            }
        }
    }

    T getsum(int top, int left, int bottom, int right){//[top, bottom), [left, right)
        return sum[bottom][right] - sum[bottom][left] - sum[top][right] + sum[top][left];
    }
};

signed main(){
    int h,w;
    ll K,v;
    cin >> h >> w >> K >> v;
    RectangleSum<ll> rs(h,w);
    ll a;
    REP(i,h){
        REP(j,w){
            cin >> a;
            rs.add(i, j, a);
        }
    }
    rs.build();
    int ans = 0;
    REP(i,h){
        REP(j,w){
            for(int k = i + 1; k <= h; k++){
                for(int l = j + 1; l <= w; l++){
                    if(rs.getsum(i, j, k, l) + (k - i) * (l - j) * K <= v){
                        ans = max(ans, (k - i) * (l - j));
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}