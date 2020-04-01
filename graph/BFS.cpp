vector<int> BFS(int s, vector<vector<int>>& G) {
    int V = G.size();
    const int INF = 1e9;
    vector<int> dist(V, INF);
    queue<int> que;
    que.emplace(s);
    dist[s] = 0;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int to : G[v]) {
            if (dist[to] == INF) {
                que.emplace(to);
                dist[to] = dist[v] + 1;
            }
        }
    }
    return dist;
}