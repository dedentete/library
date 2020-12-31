vector<int> BFS(int s, vector<vector<int>>& G) {
    int V = G.size();
    vector<int> dist(V, -1);
    queue<int> que;
    que.emplace(s);
    dist[s] = 0;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int to : G[v]) {
            if (dist[to] != -1) continue;
            que.emplace(to);
            dist[to] = dist[v] + 1;
        }
    }
    return dist;
}