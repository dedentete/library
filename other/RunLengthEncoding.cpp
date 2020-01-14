template <typename T>
vector<pair<int, T>> RLE(vector<T> v){
    int n = v.size();
    vector<pair<int, T>> res;
    T pre = v[0];
    int cnt = 1;
    for(int i = 1; i < n; i++){
        if(v[i] != pre){
            res.emplace_back(cnt, pre);
            pre = v[i];
            cnt = 0;
        }
        cnt++;
    }
    res.emplace_back(cnt, pre);
    return res;
}