vector<int> Tsort(vector<vector<int>> & G){
    vector<int> To; //トポロジカルソート後のグラフ
    // To.size() == V であればトポロジカルソートができた、そうでなければできなかったと判定できる
    int V = G.size();
    stack<int> st; //入次数が 0 の頂点の集合
    int indeg[V] = {}; //頂点の入次数を管理する配列
    for(int i = 0; i < V; i++){
        for(int j = 0; j < G[i].size(); j++){
            indeg[G[i][j]]++;
        }
    }
    for(int i = 0; i < V; i++){
        if(indeg[i] == 0){
            st.push(i);
        }
    }
    while(!st.empty()){
        int u = st.top();
        st.pop();
        To.push_back(u);
        for(int i = 0; i < G[u].size(); i++){
            indeg[G[u][i]]--; //隣接する頂点の入次数を1減らす
            //dp[G[u][i]] = max(dp[G[u][i]], dp[u] + 1);
            //ans = max(ans, dp[G[u][i]]);
            if(indeg[G[u][i]] == 0){
                st.push(G[u][i]); //入次数が 0 になればstに追加
            }
        }
    }
    return To;
}