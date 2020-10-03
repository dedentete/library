// ABC-13-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

struct Doubling {
    const int n, LOG;
    vector<vector<int>> nxt;

    Doubling(int n, int LOG = 60) : n(n), LOG(LOG) {
        nxt.resize(LOG + 1, vector<int>(n, -1));
    }

    void set_next(int idx, int x) {
        nxt[0][idx] = x;
    }

    void build() {
        for (int i = 0; i < LOG; i++) {
            for (int j = 0; j < n; j++) {
                if (nxt[i][j] == -1)
                    nxt[i + 1][j] = -1;
                else
                    nxt[i + 1][j] = nxt[i][nxt[i][j]];
            }
        }
    }

    int query(int cur, long long dist) {
        for (int i = LOG; i >= 0; i--) {
            if (cur < 0) return -1;
            if (dist & (1LL << i)) cur = nxt[i][cur];
        }
        return cur;
    }
};

signed main() {
    int n, m, d;
    cin >> n >> m >> d;
    int cur[n];
    iota(cur, cur + n, 0);
    int a;
    rep(i, m) {
        cin >> a;
        a--;
        swap(cur[a], cur[a + 1]);
    }
    int p[n];
    rep(i, n) {
        p[cur[i]] = i;
    }
    Doubling db(n, 30);
    rep(i, n) {
        db.set_next(i, p[i]);
    }
    db.build();
    rep(i, n) {
        cout << db.query(i, d) + 1 << endl;
    }
    return 0;
}