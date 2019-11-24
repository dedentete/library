vector<int> Zalgorithm(string & s){
    int n = s.size();
    vector<int> res(n);
    res[0] = n;
    int i = 1, j = 0;
    while(i < n){
        while(i + j < n && s[j] == s[i + j]) j++;
        res[i] = j;
        if(j == 0){
            i++;
            continue;
        }
        int k = 1;
        while(i + k < n && k + a[k] < j){
            res[i + k] = res[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return res;
}