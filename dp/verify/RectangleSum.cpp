// ABC86-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

template <typename T>
struct RectangleSum {
    vector<vector<T>> sum;

    RectangleSum(int h, int w) {
        init(h, w);
    }

    void init(int h, int w) {
        sum.resize(h + 1, vector<T>(w + 1, 0));
    }

    void add(int y, int x, T val) {
        y++;
        x++;
        sum[y][x] += val;
    }

    void build() {
        for (int i = 1; i < (int)sum.size(); i++) {
            for (int j = 1; j < (int)sum[i].size(); j++) {
                sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
            }
        }
    }

    T get(int top, int left, int bottom,
          int right) {  //[top, bottom), [left, right)
        return sum[bottom][right] - sum[bottom][left] - sum[top][right] +
               sum[top][left];
    }

    void print() {
        for (int y = 0; y < (int)sum.size() - 1; y++) {
            for (int x = 0; x < (int)sum[y].size() - 1; x++) {
                cout << get(y, x, y + 1, x + 1) << " ";
            }
            cout << endl;
        }
    }
};

signed main() {
    int n, k;
    cin >> n >> k;
    RectangleSum<int> rsb(2 * k, 2 * k);
    RectangleSum<int> rsw(2 * k, 2 * k);
    int cntb = 0, cntw = 0;
    int x, y;
    char c;
    rep(i, n) {
        cin >> x >> y >> c;
        x %= 2 * k;
        y %= 2 * k;
        rsb.add(y, x, c == 'B' ? 1 : -1);
        rsw.add(y, x, c == 'W' ? 1 : -1);
        cntb += c == 'B';
        cntw += c == 'W';
    }
    rsb.build();
    rsw.build();
    int ans = -INF;
    for (int y = 0; y < k; y++) {
        for (int x = 0; x < k; x++) {
            ans = max(ans, cntw + rsb.get(0, 0, y, x) +
                               rsb.get(y, x, y + k, x + k) +
                               rsb.get(y + k, x + k, 2 * k, 2 * k) +
                               rsb.get(y + k, 0, 2 * k, x) +
                               rsb.get(0, x + k, y, 2 * k));
            ans = max(ans, cntb + rsw.get(0, 0, y, x) +
                               rsw.get(y, x, y + k, x + k) +
                               rsw.get(y + k, x + k, 2 * k, 2 * k) +
                               rsw.get(y + k, 0, 2 * k, x) +
                               rsw.get(0, x + k, y, 2 * k));
        }
    }
    cout << ans << endl;
    return 0;
}