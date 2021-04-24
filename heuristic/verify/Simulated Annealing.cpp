// chokudai004
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

constexpr int N = 30;
constexpr double TIMELIMIT = 2.9;

struct XORShift {
    unsigned int x, y, z, w, t;

    XORShift(int seed) {
        mt19937 rnd(seed);
        x = rnd();
        y = rnd();
        z = rnd();
        w = rnd();
        t = 1;
    }

    int rand() {
        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w & 0x7fffffff;
    }
} rnd(rand());

struct Timer {
    chrono::high_resolution_clock::time_point start, now;

    Timer() {
        start = chrono::high_resolution_clock::now();
    }

    double getTime() {
        now = chrono::high_resolution_clock::now();
        return chrono::duration<double>(now - start).count();
    }
};

struct STATE {
    int board[N][N];
    int score;
};

STATE state;
int l[N][N], r[N][N];
int B[3];
int f[40];

void init(STATE& state) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            state.board[i][j] = l[i][j] + rnd.rand() % (r[i][j] - l[i][j] + 1);
        }
    }
    int A[3] = {};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = j; k < N; k++) {
                sum += state.board[i][k];
                if (sum > B[2]) break;
                if (f[sum] != -1) A[f[sum]]++;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = j; k < N; k++) {
                sum += state.board[k][i];
                if (sum > B[2]) break;
                if (f[sum] != -1) A[f[sum]]++;
            }
        }
    }
    state.score = A[0] * B[0] + A[1] * B[1] + A[2] * B[2];
}

void modify(STATE& state) {
    int y = rnd.rand() % N, x = rnd.rand() % N;
    int A[3] = {};
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = i; j < N; j++) {
            sum += state.board[y][j];
            if (sum > B[2]) break;
            if (f[sum] != -1) A[f[sum]]--;
        }
    }
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = i; j < N; j++) {
            sum += state.board[j][x];
            if (sum > B[2]) break;
            if (f[sum] != -1) A[f[sum]]--;
        }
    }
    state.board[y][x] = l[y][x] + rnd.rand() % (r[y][x] - l[y][x] + 1);
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = i; j < N; j++) {
            sum += state.board[y][j];
            if (sum > B[2]) break;
            if (f[sum] != -1) A[f[sum]]++;
        }
    }
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = i; j < N; j++) {
            sum += state.board[j][x];
            if (sum > B[2]) break;
            if (f[sum] != -1) A[f[sum]]++;
        }
    }
    state.score += A[0] * B[0] + A[1] * B[1] + A[2] * B[2];
}

void SA() {
    init(state);
    Timer tmr;
    double starttime = tmr.getTime();
    double starttemp = 30.0, endtemp = 1.0;
    while (true) {
        double nowtime = tmr.getTime();
        if (nowtime - starttime > TIMELIMIT) break;
        STATE newstate = state;
        modify(newstate);
        double temp = starttemp +
                      (endtemp - starttemp) * (nowtime - starttime) / TIMELIMIT;
        double prob = exp((newstate.score - state.score) / temp);
        if (prob > (rnd.rand() % (int)1e9) / 1e9) {
            state = newstate;
        }
    }
}

signed main() {
    int n;
    cin >> n >> B[0] >> B[1] >> B[2];
    fill(f, f + 40, -1);
    rep(i, 3) {
        f[B[i]] = i;
    }
    rep(i, N) {
        rep(j, N) {
            cin >> l[i][j];
        }
    }
    rep(i, N) {
        rep(j, N) {
            cin >> r[i][j];
        }
    }
    SA();
    rep(i, N) {
        rep(j, N) {
            if (j) cout << " ";
            cout << state.board[i][j];
        }
        cout << endl;
    }
    return 0;
}