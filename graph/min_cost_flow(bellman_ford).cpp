#define MAX_V 100

//辺を表す構造体（行き先、容量、コスト、逆辺）
struct edge{int to, cap, cost, rev; };

int V;//頂点数
vector<edge> G[MAX_V];//グラフの隣接リスト表現
int dist[MAX_V];//最短距離
int prevv[MAX_V], preve[MAX_V];//直前の頂点と辺

//fromからtoへ向かう容量cap、コストcostの辺をグラフに追加する
void add_edge(int from, int to, int cap, int cost){
    G[from].push_back((edge){to, cap, cost, G[to].size()});
    G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
}

//sからtへの流量fの最小費用流を求める
//流せない場合は-1を返す
int min_cost_flow(int s, int t, int f){
    int res = 0;
    while(f > 0){
        //ベルマンフォード法により、s-t間最短路を求める
        fill(dist, dist + V, INF);
        dist[s] = 0;
        bool update = true;
        while(update){
            update = false;
            for(int v = 0; v < V; v++){
                if(dist[v] == INF) continue;
                for(int i = 0; i < G[v].size(); i++){
                    edge &e = G[v][i];
                    if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
                        dist[e.to] = dist[v] + e.cost;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        update = true;
                    }
                }
            }
        }
        
        if(dist[t] == INF){
            //これ以上流せない
            return -1;
        }

        //s-t間最短路に沿って目一杯流す
        int d = f;
        for(int v = t; v != s; v = prevv[v]){
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * dist[t];
        for(int v = t; v != s; v = prevv[v]){
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}