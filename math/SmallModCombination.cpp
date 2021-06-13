/*
    MODint依存
    nCk mod p (p < n)
*/
template <typename T>
struct SmallModCombination {
    vector<int> f;
    vector<T> g;

    SmallModCombination(int sz) : f(sz + 1), g(sz + 1) {
        for (int i = 1; i <= sz; i++) {
            int pos = i;
            while (pos % g[0].mod() == 0) {
                pos /= g[0].mod();
                f[i]++;
            }
            g[i] = T(pos);
        }
        g[0] = T(1);
        for (int i = 1; i <= sz; i++) f[i] += f[i - 1];
        for (int i = 1; i <= sz; i++) g[i] *= g[i - 1];
    }

    T C(int n, int k) {
        if (f[n] > f[k] + f[n - k])
            return T(0);
        else
            return g[n] / (g[k] * g[n - k]);
    }
};