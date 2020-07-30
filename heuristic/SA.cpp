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
    score;
};

void init(STATE& state) {}

void modify(STATE& state) {}

STATE state;
constexpr double TIMELIMIT = 1.9;

void SA() {
    init(state);
    double starttemp, endtemp;
    Timer tmr;
    double startclock = tmr.getTime();
    while (true) {
        double nowclock = tmr.getTime();
        if (nowclock - startclock > TIMELIMIT) break;
        STATE newstate = state;
        modify(newstate);
        double temp = starttemp + (endtemp - starttemp) *
                                      (nowclock - startclock) / TIMELIMIT;
        double prob = exp((newstate.score - state.score) / temp);
        if (prob > (rnd.rand() % (int)1e9) / 1e9) {
            state = newstate;
        }
    }
}