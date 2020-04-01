/*
    MODint依存
*/
template <typename T>
struct Comb {
    vector<T> fac, fin;

    Comb(int sz) : fac(sz + 1), fin(sz + 1) {
        fac[0] = fin[sz] = T(1);
        for (int i = 1; i <= sz; i++) {
            fac[i] = fac[i - 1] * T(i);
        }
        fin[sz] /= fac[sz];
        for (int i = sz - 1; i >= 0; i--) {
            fin[i] = fin[i + 1] * T(i + 1);
        }
    }

    /* 階乗 */
    inline T fact(int k) const {
        return fac[k];
    }

    inline T finv(int k) const {
        return fin[k];
    }

    /* 順列 */
    T P(int n, int k) const {
        if (k < 0 || n < k) return T(0);
        return fac[n] * fin[n - k];
    }

    /* 組み合わせ */
    T C(int n, int k) const {
        if (k < 0 || n < k) return T(0);
        return fac[n] * fin[n - k] * fin[k];
    }

    /* 重複組み合わせ */
    T H(int n, int k) const {
        if (n < 0 || k < 0) return T(0);
        return k == 0 ? T(1) : C(n + k - 1, k);
    }

    /* ベル数 */
    T B(int n, int k) const {
        if (n == 0) return T(1);
        k = min(k, n);
        vector<T> dp(k + 1);
        dp[0] = T(1);
        for (int i = 1; i <= k; i++) {
            if (i & 1)
                dp[i] = dp[i - 1] - fin[i];
            else
                dp[i] = dp[i - 1] + fin[i];
        }
        T res(0);
        for (int i = 1; i <= k; i++) {
            /* MODint依存 */
            res += T(i).pow(n) * fin[i] * dp[k - i];
        }
        return res;
    }

    /* スターリング数 */
    T S(int n, int k) const {
        T res(0);
        for (int i = 1; i <= k; i++) {
            /* MODint依存 */
            T t = C(k, i) * T(i).pow(n);
            if ((k - i) & 1)
                res -= t;
            else
                res += t;
        }
        return res * fin[k];
    }
};

/*
    P(5, 3)の場合 :
    0 + 0 + 5 = 0 + 1 + 4 = 0 + 2 + 3 = 1 + 1 + 3 = 1 + 2 + 2
    よって、P(5, 3) = 5
*/
template <typename T>
struct Partition {
    vector<vector<T>> dp;

    Partition(int sz) : dp(sz + 1, vector<T>(sz + 1)) {
        dp[0][0] = T(1);
        for (int i = 0; i <= sz; i++) {
            for (int j = 1; j <= sz; j++) {
                if (i - j >= 0)
                    dp[i][j] = dp[i][j - 1] + dp[i - j][j];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
    }

    /* 分割数 */
    T P(int n, int k) {
        if (n < 0 || k < 0) return T(0);
        return dp[n][k];
    }
};

/*
    MODint依存
    計算量 : O(k)
*/
template <typename T>
T C(long long n, int k) {
    T num(1), denom(1);
    for (int i = 0; i < k; i++) {
        num *= T(n - i);
        denom *= T(i + 1);
    }
    return num / denom;
}