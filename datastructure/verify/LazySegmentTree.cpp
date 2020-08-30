// ABC128-E
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

template <typename Operator>
struct LazySegmentTree {
    using NodeType = typename Operator::NodeType;
    using LazyType = typename Operator::LazyType;
    int n;
    int length;
    int height;
    vector<NodeType> node;
    vector<LazyType> lazy;
    vector<pair<int, int>> range;

    void propagate(int k) {
        if (lazy[k] == Operator::unitlazy) return;
        node[k] = Operator::funcMerge(node[k], lazy[k],
                                      range[k].second - range[k].first);
        if (k < length)
            lazy[2 * k + 0] = Operator::funcLazy(lazy[2 * k + 0], lazy[k]);
        if (k < length)
            lazy[2 * k + 1] = Operator::funcLazy(lazy[2 * k + 1], lazy[k]);
        lazy[k] = Operator::unitlazy;
    }

    LazySegmentTree(const int n) : n(n) {
        length = 1;
        height = 0;
        while (length < n) length *= 2, height++;
        node.resize(2 * length, Operator::unitnode);
        lazy.resize(2 * length, Operator::unitlazy);
        range.resize(2 * length);
        for (int i = length - 1; i >= 0; i--)
            node[i] =
                Operator::funcNode(node[(i << 1) + 0], node[(i << 1) + 1]);
        for (int i = 0; i < length; i++)
            range[i + length] = make_pair(i, i + 1);
        for (int i = length - 1; i >= 0; --i)
            range[i] = make_pair(range[(i << 1) + 0].first,
                                 range[(i << 1) + 1].second);
    }

    LazySegmentTree(const int n, const NodeType init) : n(n) {
        length = 1;
        height = 0;
        while (length < n) length *= 2, height++;
        node.resize(2 * length, Operator::unitnode);
        lazy.resize(2 * length, Operator::unitlazy);
        range.resize(2 * length);
        for (int i = 0; i < n; i++) node[i + length] = init;
        for (int i = length - 1; i >= 0; i--)
            node[i] =
                Operator::funcNode(node[(i << 1) + 0], node[(i << 1) + 1]);
        for (int i = 0; i < length; i++)
            range[i + length] = make_pair(i, i + 1);
        for (int i = length - 1; i >= 0; --i)
            range[i] = make_pair(range[(i << 1) + 0].first,
                                 range[(i << 1) + 1].second);
    }

    LazySegmentTree(const vector<NodeType>& vec) : n(vec.size()) {
        length = 1;
        height = 0;
        while (length < n) length *= 2, height++;
        node.resize(2 * length, Operator::unitnode);
        lazy.resize(2 * length, Operator::unitlazy);
        range.resize(2 * length);
        for (int i = 0; i < vec.size(); i++) node[i + length] = vec[i];
        for (int i = length - 1; i >= 0; i--)
            node[i] =
                Operator::funcNode(node[(i << 1) + 0], node[(i << 1) + 1]);
        for (int i = 0; i < length; i++)
            range[i + length] = make_pair(i, i + 1);
        for (int i = length - 1; i >= 0; --i)
            range[i] = make_pair(range[(i << 1) + 0].first,
                                 range[(i << 1) + 1].second);
    }

    // update[a,b)
    void update(int a, int b, LazyType x) {
        int l = a + length, r = b + length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        for (r++; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                lazy[l] = Operator::funcLazy(lazy[l], x), propagate(l), l++;
            if (r & 1)
                --r, lazy[r] = Operator::funcLazy(lazy[r], x), propagate(r);
        }
        l = a + length, r = b + length - 1;
        while ((l >>= 1), (r >>= 1), l) {
            if (lazy[l] == Operator::unitlazy)
                node[l] = Operator::funcNode(
                    Operator::funcMerge(
                        node[(l << 1) + 0], lazy[(l << 1) + 0],
                        range[(l << 1) + 0].second - range[(l << 1) + 0].first),
                    Operator::funcMerge(node[(l << 1) + 1], lazy[(l << 1) + 1],
                                        range[(l << 1) + 1].second -
                                            range[(l << 1) + 1].first));
            if (lazy[r] == Operator::unitlazy)
                node[r] = Operator::funcNode(
                    Operator::funcMerge(
                        node[(r << 1) + 0], lazy[(r << 1) + 0],
                        range[(r << 1) + 0].second - range[(r << 1) + 0].first),
                    Operator::funcMerge(node[(r << 1) + 1], lazy[(r << 1) + 1],
                                        range[(r << 1) + 1].second -
                                            range[(r << 1) + 1].first));
        }
    }

    // get [a,b)
    NodeType get(int a, int b) {
        int l = a + length, r = b + length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        NodeType vl = Operator::unitnode, vr = Operator::unitnode;
        for (r++; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                vl = Operator::funcNode(
                    vl, Operator::funcMerge(node[l], lazy[l],
                                            range[l].second - range[l].first)),
                l++;
            if (r & 1)
                r--, vr = Operator::funcNode(
                         Operator::funcMerge(node[r], lazy[r],
                                             range[r].second - range[r].first),
                         vr);
        }
        return Operator::funcNode(vl, vr);
    }

    void print() {
        for (int i = 0; i < n; i++) cout << get(i, i + 1) << " ";
        cout << endl;
    }
};

template <typename T, typename U>
struct RangeMinRangeAdd {
    using NodeType = T;
    using LazyType = U;
    static constexpr NodeType unitnode = 1e9;
    static constexpr LazyType unitlazy = 0;
    static constexpr NodeType funcNode(NodeType l, NodeType r) {
        return min(l, r);
    }
    static constexpr LazyType funcLazy(LazyType l, LazyType r) {
        return l + r;
    }
    static constexpr NodeType funcMerge(NodeType l, LazyType r, int len) {
        return l + r;
    }
};

/*
    unitlazyは更新され得ない値にする必要がある
*/
template <typename T, typename U>
struct RangeSumRangeUpdate {
    using NodeType = T;
    using LazyType = U;
    static constexpr NodeType unitnode = 0;
    static constexpr LazyType unitlazy = -1e9 - 1;
    static constexpr NodeType funcNode(NodeType l, NodeType r) {
        return l + r;
    }
    static constexpr LazyType funcLazy(LazyType l, LazyType r) {
        return r;
    }
    static constexpr NodeType funcMerge(NodeType l, LazyType r, int len) {
        return r != -1e9 - 1 ? r * len : l;
    }
};

template <typename T, typename U>
struct RangeSumRangeAdd {
    using NodeType = T;
    using LazyType = U;
    static constexpr NodeType unitnode = 0;
    static constexpr LazyType unitlazy = 0;
    static constexpr NodeType funcNode(NodeType l, LazyType r) {
        return l + r;
    }
    static constexpr LazyType funcLazy(LazyType l, LazyType r) {
        return l + r;
    }
    static constexpr NodeType funcMerge(NodeType l, LazyType r, int len) {
        return l + r * len;
    }
};

signed main() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, pair<int, int>>> v;
    int s, t, x;
    rep(i, n) {
        cin >> s >> t >> x;
        v.emplace_back(
            pair<int, pair<int, int>>(x, pair<int, int>(s - x, t - x)));
    }
    int d[q];
    rep(i, q) {
        cin >> d[i];
    }
    sort(ALL(v));
    reverse(ALL(v));
    LazySegmentTree<RangeSumRangeUpdate<int, int>> seg(q, -1);
    rep(i, n) {
        int l = lower_bound(d, d + q, v[i].second.first) - d;
        int r = lower_bound(d, d + q, v[i].second.second) - d;
        seg.update(l, r, v[i].first);
    }
    rep(i, q) {
        cout << seg.get(i, i + 1) << endl;
    }
    return 0;
}