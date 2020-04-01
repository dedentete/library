template <typename FT, typename CT>
struct PrimalDual {
    struct edge {
        int to;
        FT cap;
        CT cost;
        int rev;
        edge(int to, FT cap, CT cost, int rev)
            : to(to), cap(cap), cost(cost), rev(rev) {}
    };

    const CT INF;
    vector<vector<edge>> G;
    vector<CT> h, dist;
    vector<int> prevv, preve;

    PrimalDual(int n, CT INF = 1e9)
        : G(n), h(n), dist(n), prevv(n), preve(n), INF(INF) {}

    void add_edge(int u, int v, FT cap, CT cost) {
        G[u].emplace_back(v, cap, cost, G[v].size());
        G[v].emplace_back(u, 0, -cost, G[u].size() - 1);
    }

    void Dijkstra(int s) {
        using P = pair<CT, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (int i = 0; i < G[v].size(); i++) {
                edge& e = G[v][i];
                if (e.cap == 0) continue;
                if (dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
    }

    CT flow(int s, int t, FT f) {
        CT res = 0;
        fill(h.begin(), h.end(), 0);
        while (f > 0) {
            Dijkstra(s);
            if (dist[t] == INF) return -1;
            for (int v = 0; v < h.size(); v++) {
                if (dist[v] < INF) h[v] = h[v] + dist[v];
            }
            FT d = f;
            for (int v = t; v != s; v = prevv[v]) {
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res = res + h[t] * d;
            for (int v = t; v != s; v = prevv[v]) {
                edge& e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};