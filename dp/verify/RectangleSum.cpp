//ARC-25-B
#include <bits/stdc++.h>
using namespace std;
#define REP(i,a) for(int i = 0; i < (a); i++)
#define ALL(a) (a).begin(),(a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const int MOD = 1e9 + 7;

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

    T getsum(int top, int left, int bottom, int right){//[top, bottom], [left, right]
        return sum[bottom + 1][right + 1] - sum[bottom + 1][left] - sum[top][right + 1] + sum[top][left];
    }
};

signed main(){
    int h,w;
    cin >> h >> w;
    int c;
    RectangleSum<int> black(h, w), white(h, w);
    REP(i,h){
        REP(j,w){
            cin >> c;
            if((i + j) % 2 == 0){
                black.add(i, j, c);
            }else{
                white.add(i, j, c);
            }
        }
    }
    black.build();
    white.build();
    int ans = 0;
    REP(i,h){
        REP(j,w){
            for(int k = i; k < h; k++){
                for(int l = j; l < w; l++){
                    if(black.getsum(i, j, k, l) == white.getsum(i, j, k, l)){
                        ans = max(ans, (k - i + 1) * (l - j + 1));
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}