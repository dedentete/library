// ABC-177-E
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

#define MAX 1000000

struct osa_k {
    vector<int> minfactor;

    osa_k(int n) {
        eratos(n);
    }

    vector<int> eratos(int n) {
        minfactor.resize(n + 1);
        iota(minfactor.begin(), minfactor.end(), 0);
        for (int i = 2; i * i <= n; i++) {
            if (minfactor[i] < i) continue;
            for (int j = i * i; j <= n; j += i) {
                if (minfactor[j] == j) minfactor[j] = i;
            }
        }
        return minfactor;
    }

    map<int, int> PrimeFactor(int n) {
        map<int, int> mp;
        while (n > 1) {
            mp[minfactor[n]]++;
            n /= minfactor[n];
        }
        return mp;
    }
};

signed main() {
    int n;
    cin >> n;
    int a[n];
    rep(i, n) {
        cin >> a[i];
    }
    osa_k os(MAX);
    bool visited[MAX + 1] = {};
    bool flag = true;
    rep(i, n) {
        auto pf = os.PrimeFactor(a[i]);
        for (auto p : pf) {
            if (visited[p.first]) {
                flag = false;
                goto fin;
            }
            visited[p.first] = true;
        }
    }
fin:;
    if (flag) {
        cout << "pairwise coprime" << endl;
        return 0;
    }
    int g = a[0];
    rep(i, n) {
        g = gcd(g, a[i]);
    }
    cout << (g == 1 ? "setwise coprime" : "not coprime") << endl;
    return 0;
}