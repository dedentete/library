/*
    vector<long long> a(n) を座圧する場合 : 
    auto v = compress(a);
    auto m = dict(v);
    i番目の要素の取り出し方 : 
    m[a[i]]
*/
template<typename T>
vector<T> compress(vector<T> vec){
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    return vec;
}

template<typename T>
map<T, int> dict(vector<T> & vec){
    map<T, int> res;
    for(int i = 0; i < (int)vec.size(); i++){
        res[vec[i]] = i;
    }
    return res;
}