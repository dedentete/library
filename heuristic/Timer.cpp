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