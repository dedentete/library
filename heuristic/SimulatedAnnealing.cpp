constexpr double TIMELIMIT = 1.9;

struct XorShift {
    unsigned int x, y, z, w, t;

    XorShift(int seed) {
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
};

void calc(State& state) {
    
}

void init(State& state) {
    
    calc(state);
}

void modify(State& state) {
    
    calc(state);
}

void solve(State& state) {
    int steps = 0;
    Timer tmr;
    double start_time = tmr.getTime();
    // double start_temp, end_temp;
    while (true) {
        double current_time = tmr.getTime();
        if (current_time - start_time > TIMELIMIT) break;
        State newstate = state;
        modify(newstate);
        if (newstate.score > state.score) {
            state = newstate;
        }
        /*
        double temp = start_temp + (end_temp - start_temp) *
                                      (current_time - start_time) / TIMELIMIT;
        double prob = exp((newstate.score - state.score) / _temp);
        if (prob > (rnd.rand() % (int)1e9) / 1e9) {
            state = newstate;
        }
        */
        steps++;
    }
    cerr << "score : " << state.score << endl;
    cerr << "steps : " << steps << endl;
}