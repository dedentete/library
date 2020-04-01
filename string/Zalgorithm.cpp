template <typename T>
vector<int> Zalgorithm(const vector<T>& v) {
    int n = v.size();
    vector<int> res(n);
    res[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i + j < n && v[j] == v[i + j]) j++;
        res[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < n && k + res[k] < j) {
            res[i + k] = res[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return res;
}

vector<int> Zalgorithm(const string& s) {
    return Zalgorithm(vector<char>(s.begin(), s.end()));
}