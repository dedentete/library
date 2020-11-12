// https://beet-aizu.github.io/library/segtree/basic/dual.cpp
template <typename E>
struct DualSegmentTree {
    using H = function<E(E, E)>;
    int n, height;
    H h;
    E ei;
    vector<E> laz;

    DualSegmentTree(H h, E ei) : h(h), ei(ei) {}

    void init(int n_) {
        n = 1;
        height = 0;
        while (n < n_) n <<= 1, height++;
        laz.assign(2 * n, ei);
    }

    inline void propagate(int k) {
        if (laz[k] == ei) return;
        laz[(k << 1) | 0] = h(laz[(k << 1) | 0], laz[k]);
        laz[(k << 1) | 1] = h(laz[(k << 1) | 1], laz[k]);
        laz[k] = ei;
    }

    inline void thrust(int k) {
        for (int i = height; i; i--) propagate(k >> i);
    }

    void update(int a, int b, E x) {
        if (a >= b) return;
        thrust(a += n);
        thrust(b += n - 1);
        for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) laz[l] = h(laz[l], x), l++;
            if (r & 1) --r, laz[r] = h(laz[r], x);
        }
    }

    void update(int a, E x) {
        thrust(a += n);
        laz[a] = x;
    }

    E get(int a) {
        thrust(a += n);
        return laz[a];
    }
};