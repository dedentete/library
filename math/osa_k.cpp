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