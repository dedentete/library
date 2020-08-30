template <typename T>
vector<T> Dijkstra(int s, vector<vector<pair<int, T>>>& G,
                   /*vector<int> & prev,*/ const T INF = 1e9) {
    using P = pair<T, int>;
    int V = G.size();
    vector<T> dist(V, INF);
    priority_queue<P, vector<P>, greater<P>> que;
    dist[s] = 0;
    que.emplace(0, s);
    // prev.assign(V, -1);
    while (!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i = 0; i < (int)G[v].size(); i++) {
            int to = G[v][i].first;
            T cost = G[v][i].second;
            if (dist[to] > dist[v] + cost) {
                dist[to] = dist[v] + cost;
                // prev[to] = v;
                que.emplace(dist[to], to);
            }
        }
    }
    return dist;
}