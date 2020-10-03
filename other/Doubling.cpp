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