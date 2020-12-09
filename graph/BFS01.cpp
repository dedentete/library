vector<int> BFS01(int s, vector<vector<pair<int, int>>>& G,
                  const int INF = 1e9) {
    int V = G.size();
    vector<int> dist(V, INF);
    deque<int> que;
    dist[s] = 0;
    que.push_front(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop_front();
        for (int i = 0; i < (int)G[v].size(); i++) {
            int to = G[v][i].first, cost = G[v][i].second;
            if (dist[to] != INF) continue;
            if (cost == 1) {
                que.push_back(to);
                dist[to] = dist[v] + 1;
            } else {
                que.push_front(to);
                dist[to] = dist[v];
            }
        }
    }
    return dist;
}