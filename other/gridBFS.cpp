vector<vector<int>> gridBFS(vector<string> & s, int sy, int sx, char wall = '#', const int INF = 1e9){
    const int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
    int h = s.size(), w = s[0].size();
    vector<vector<int>> dist(h, vector<int>(w, INF));
    queue<pair<int, int>> que;
    que.emplace(sy, sx);
    dist[sy][sx] = 0;
    while(!que.empty()){
        pair<int, int> p = que.front();
        que.pop();
        for(int i = 0; i < 4; i++){
            int ny = p.first + dy[i], nx = p.second + dx[i];
            if(0 <= ny && ny < h && 0 <= nx && nx < w && s[ny][nx] != wall && dist[ny][nx] == INF){
                que.emplace(ny, nx);
                dist[ny][nx] = dist[p.first][p.second] + 1;
            }
        }
    }
    return dist;
}