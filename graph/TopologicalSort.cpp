/*
    To.size() == V であればトポロジカルソートができた、そうでなければできなかったと判定できる
*/
vector<int> Tsort(vector<vector<int>> & G){
    vector<int> To;
    int V = G.size();
    stack<int> st;
    int indeg[V] = {};
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
    //vector<int> dp(V);
    while(!st.empty()){
        int u = st.top();
        st.pop();
        To.push_back(u);
        for(int i = 0; i < G[u].size(); i++){
            indeg[G[u][i]]--;
            //dp[G[u][i]] = max(dp[G[u][i]], dp[u] + 1);
            //ans = max(ans, dp[G[u][i]]);
            if(indeg[G[u][i]] == 0){
                st.push(G[u][i]);
            }
        }
    }
    return To;
}