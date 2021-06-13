template <typename T>
struct BIT {
    int n;
    vector<T> dat;

    BIT(int n) : n(n), dat(n + 1, 0) {}

    T sum(int idx) {  // 1-indexed
        T res(0);
        for (int i = idx; i > 0; i -= i & -i) res += dat[i];
        return res;
    }

    T sum(int l, int r) {  // 0-indexed
        return sum(r) - sum(l);
    }

    void add(int idx, T x) {  // 0-indexed
        idx++;
        for (int i = idx; i <= n; i += i & -i) dat[i] += x;
    }

    int lower_bound(T x) {
        if (x <= 0) return T(0);
        int res = 0, r = 1;
        while (r < n) r <<= 1;
        for (; r > 0; r >>= 1) {
            if (res + r <= n && dat[res + r] < x) {
                x -= dat[res + r];
                res += r;
            }
        }
        return res;
    }

    int upper_bound(T x) {
        return lower_bound(x + 1);
    }

    void print() {
        for (int i = 0; i < n; i++) cout << sum(i, i + 1) << " ";
        cout << endl;
    }
};