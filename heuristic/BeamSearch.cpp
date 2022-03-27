constexpr int BEAM_SIZE = 1;

struct Timer {
    chrono::system_clock::time_point start, now;

    Timer() {
        start = chrono::system_clock::now();
    }

    double getTime() {
        now = chrono::system_clock::now();
        return chrono::duration<double>(now - start).count();
    }
};

struct State {
    int score;
    bool operator<(const State& a) const {
        return score < a.score;
    };
};

void calc(State& state) {

}

void init(State& state) {

    calc(state);
}

void modify(State& state, int r, int c, int s, int turn) {

    calc(state);
}

void solve(State& state) {
    priority_queue<State> que;
    que.emplace(state);
    Timer tmr;
    double start_time = tmr.getTime();
    rep(_, ) {
        priority_queue<State> nxt;
        while (!que.empty()) {
            State state = que.top();
            que.pop();
            
        }
        rep(k, BEAM_SIZE) {
            que.emplace(nxt.top());
            nxt.pop();
        }
        double current_time = tmr.getTime();
        if (current_time - start_time > TIMELIMIT) break;
    }
    state = que.top();
    cerr << "state : " << state.score << endl;
}