/*
    1-indexed であることに注意 !!
*/
template <typename T>
struct BIT {
    int n;
    vector<T> dat;

    BIT(int n) : n(n), dat(n + 1, 0) {}

    T sum(int a) {
        T res = 0;
        for (int i = a; i > 0; i -= (i & (-i))) res += dat[i];
        return res;
    }

    T sum(int a, int b) {
        return sum(b - 1) - sum(a - 1);
    }

    void add(int k, T x) {
        if (k == 0) return;
        for (int i = k; i <= n; i += (i & (-i))) dat[i] += x;
    }

    /*
        a[0] + a[1] + ... + a[res] >= x
    */
    int lower_bound(T x) {
        if (x <= 0) return T(0);
        int res = 0, k = 1;
        while (k < n) k <<= 1;
        for (; k > 0; k >>= 1) {
            if (res + k <= n && dat[res + k] < x) {
                x -= dat[res + k];
                res += k;
            }
        }
        return res + 1;
    }
};