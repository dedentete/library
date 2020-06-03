template <typename T>
map<T, int> compress(vector<T> vec) {
    map<T, int> res;
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int i = 0; i < (int)vec.size(); i++) {
        res[vec[i]] = i;
    }
    return res;
}