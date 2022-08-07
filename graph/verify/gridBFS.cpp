// ABC-151-D
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a) for (int i = 0; i < (a); i++)
#define ALL(a) (a).begin(), (a).end()
typedef long long ll;
typedef pair<int, int> P;
const int INF = 1e9;
const long long LINF = 1e18;
const long long MOD = 1e9 + 7;

vector<vector<int>> gridBFS(vector<string>& s, int sy, int sx, char wall = '#',
                            const int INF = 1e9) {
    const int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
    int h = s.size(), w = s[0].size();
    vector<vector<int>> dist(h, vector<int>(w, INF));
    queue<pair<int, int>> que;
    que.emplace(sy, sx);
    dist[sy][sx] = 0;
    while (!que.empty()) {
        pair<int, int> p = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            int ny = p.first + dy[i], nx = p.second + dx[i];
            if (0 <= ny && ny < h && 0 <= nx && nx < w && s[ny][nx] != wall &&
                dist[ny][nx] == INF) {
                que.emplace(ny, nx);
                dist[ny][nx] = dist[p.first][p.second] + 1;
            }
        }
    }
    return dist;
}

signed main() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    REP(i, h) {
        cin >> s[i];
    }
    int ans = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (s[y][x] == '.') {
                vector<vector<int>> dist = gridBFS(s, y, x, '#', -1);
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j++) {
                        ans = max(ans, dist[i][j]);
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}