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