vector<int> BFS(int s, vector<vector<int>>& G) {
    int V = G.size();
    vector<int> dist(V, -1);
    queue<int> que;
    dist[s] = 0;
    que.emplace(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int to : G[v]) {
            if (dist[to] != -1) continue;
            dist[to] = dist[v] + 1;
            que.emplace(to);
        }
    }
    return dist;
}