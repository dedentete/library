vector<int> BFS01(int s, vector<vector<pair<int, int>>>& G) {
    int V = G.size();
    vector<int> dist(V, -1);
    deque<int> que;
    dist[s] = 0;
    que.push_front(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop_front();
        for (int i = 0; i < (int)G[v].size(); i++) {
            int to = G[v][i].first, cost = G[v][i].second;
            if (dist[to] != -1) continue;
            if (cost == 1) {
                dist[to] = dist[v] + 1;
                que.push_back(to);
            } else {
                dist[to] = dist[v];
                que.push_front(to);
            }
        }
    }
    return dist;
}