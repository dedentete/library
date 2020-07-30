template <typename T>
vector<T> compress(vector<T> vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    return vec;
}

template <typename T>
map<T, int> dict(vector<T>& vec) {
    map<T, int> res;
    for (int i = 0; i < (int)vec.size(); i++) {
        res[vec[i]] = i;
    }
    return res;
}