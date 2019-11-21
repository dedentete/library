/*
    辺が存在しない場合、dist[i][j] = INF、ただしdist[i][i] = 0 とする
    頂点数 V のとき : 
    vector<vector<int>> dist(V, vector<int>(V, INF));
    for(int i = 0; i < V; i++){
        dist[i][i] = 0;
    }
*/
template <typename T>
void WarshallFloyd(vector<vector<T>> & dist){
    int V = dist.size();
    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    // dist[i][i] < 0 が存在 <-> 負の閉路が存在
}