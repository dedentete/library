// JOI2019yo-D
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
using P = pair<int, int>;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

template <typename T>
map<T, int> compress(vector<T> vec) {
    map<T, int> res;
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        res[vec[i]] = i;
    }
    return res;
}

signed main() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto mp = compress(a);
    int m = mp.size();
    int imos[m + 1] = {};
    for (int i = 0; i < n; i++) {
        if (!(a[i] < a[i + 1])) continue;
        imos[mp[a[i]]]++;
        imos[mp[a[i + 1]]]--;
    }
    for (int i = 0; i < m; i++) {
        imos[i + 1] += imos[i];
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        ans = max(ans, imos[i]);
    }
    cout << ans << endl;
    return 0;
}