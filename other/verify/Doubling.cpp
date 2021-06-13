// ABC-175-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int MOD = 1000000007;

struct Doubling {
    const int n, LOG;
    vector<vector<int>> nxt;
    vector<vector<ll>> sum;
    vector<vector<ll>> mx;

    Doubling(int n, int LOG = 60) : n(n), LOG(LOG) {
        nxt.resize(LOG + 1, vector<int>(n, -1));
        sum.resize(LOG + 1, vector<ll>(n, 0));
        mx.resize(LOG + 1, vector<ll>(n, 0));
    }

    void set_next(int idx, int x, ll y) {
        nxt[0][idx] = x;
        sum[0][idx] = y;
        mx[0][idx] = y;
    }

    void build() {
        for (int i = 0; i < LOG; i++) {
            for (int j = 0; j < n; j++) {
                if (nxt[i][j] == -1) {
                    nxt[i + 1][j] = -1;
                } else {
                    nxt[i + 1][j] = nxt[i][nxt[i][j]];
                    sum[i + 1][j] = sum[i][j] + sum[i][nxt[i][j]];
                    mx[i + 1][j] = max(mx[i][j], sum[i][j] + mx[i][nxt[i][j]]);
                }
            }
        }
    }

    ll query(int cur, long long dist) {
        ll cursum = 0, res = LLONG_MIN;
        for (int i = LOG; i >= 0; i--) {
            if (cur < 0) return -1;
            if (dist & (1LL << i)) {
                res = max(res, cursum + mx[i][cur]);
                cursum += sum[i][cur];
                cur = nxt[i][cur];
            }
        }
        return res;
    }
};

signed main() {
    int n;
    ll k;
    cin >> n >> k;
    int p[n];
    rep(i, n) {
        cin >> p[i];
        p[i]--;
    }
    int c[n];
    rep(i, n) {
        cin >> c[i];
    }
    Doubling d(n);
    rep(i, n) {
        d.set_next(i, p[i], c[i]);
    }
    d.build();
    ll ans = LLONG_MIN;
    rep(i, n) {
        ans = max(ans, d.query(i, k));
    }
    cout << ans << endl;
    return 0;
}