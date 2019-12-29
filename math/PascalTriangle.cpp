template <typename T>
vector<vector<T>> PascalTriangle(int n){
    vector<vector<T>> C(n + 1, vector<T>(n + 1));
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C;
}