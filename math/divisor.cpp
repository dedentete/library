vector<long long> divisor(long long n) {
    vector<long long> res;
    for (int i = 1; (long long)i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    sort(begin(res), end(res));
    return res;
}