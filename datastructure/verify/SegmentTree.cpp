// joisc2011-bookshelf
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 1e9;
constexpr long long LINF = 1e18;
constexpr long long MOD = 1e9 + 7;

template <typename Operator>
struct SegmentTree {
    using NodeType = typename Operator::NodeType;
    int n;
    int length;
    vector<NodeType> node;

    SegmentTree(const int n) : n(n) {
        length = 1;
        while (length < n) length *= 2;
        node.resize(2 * length, Operator::unitnode);
        for (int i = length - 1; i >= 0; i--)
            node[i] =
                Operator::funcNode(node[(i << 1) + 0], node[(i << 1) + 1]);
    }

    SegmentTree(const int n, const NodeType init) : n(n) {
        length = 1;
        while (length < n) length *= 2;
        node.resize(2 * length, Operator::unitnode);
        for (int i = 0; i < n; i++) node[i + length] = init;
        for (int i = length - 1; i >= 0; i--)
            node[i] =
                Operator::funcNode(node[(i << 1) + 0], node[(i << 1) + 1]);
    }

    SegmentTree(const vector<NodeType>& vec) : n(vec.size()) {
        length = 1;
        while (length < n) length *= 2;
        node.resize(2 * length, Operator::unitnode);
        for (int i = 0; i < vec.size(); i++) node[i + length] = vec[i];
        for (int i = length - 1; i >= 0; i--)
            node[i] =
                Operator::funcNode(node[(i << 1) + 0], node[(i << 1) + 1]);
    }

    void update(int idx, const NodeType x) {
        if (idx < 0 || length <= idx) return;
        idx += length;
        node[idx] = Operator::funcMerge(node[idx], x);
        while (idx >>= 1)
            node[idx] =
                Operator::funcNode(node[(idx << 1) + 0], node[(idx << 1) + 1]);
    }

    NodeType get(int l, int r) {
        if (l < 0 || length <= l || r < 0 || length < r)
            return Operator::unitnode;
        NodeType vl = Operator::unitnode, vr = Operator::unitnode;
        for (l += length, r += length; l < r; l >>= 1, r >>= 1) {
            if (l & 1) vl = Operator::funcNode(vl, node[l++]);
            if (r & 1) vr = Operator::funcNode(node[--r], vr);
        }
        return Operator::funcNode(vl, vr);
    }

    void print() {
        for (int i = 0; i < n; i++) cout << get(i, i + 1) << " ";
        cout << endl;
    }
};

template <typename T>
struct RangeMinPointUpdate {
    using NodeType = T;
    static constexpr NodeType unitnode = 1e9;
    static constexpr NodeType funcNode(NodeType l, NodeType r) {
        return min(l, r);
    }
    static constexpr NodeType funcMerge(NodeType l, NodeType r) {
        return r;
    }
};

template <typename T>
struct RangeMaxPointUpdate {
    using NodeType = T;
    static constexpr NodeType unitnode = -1e9;
    static constexpr NodeType funcNode(NodeType l, NodeType r) {
        return max(l, r);
    }
    static constexpr NodeType funcMerge(NodeType l, NodeType r) {
        return r;
    }
};

signed main() {
    int n;
    cin >> n;
    ll sum = 0;
    ll a[n];
    rep(i, n) {
        cin >> a[i];
        sum += a[i];
    }
    int pos[n];
    rep(i, n) {
        cin >> pos[i];
        pos[i]--;
    }
    SegmentTree<RangeMaxPointUpdate<ll>> dp(n + 1);
    dp.update(0, 0);
    for (int i = 0; i < n; i++) {
        dp.update(pos[i] + 1, dp.get(0, pos[i] + 1) + a[pos[i]]);
    }
    cout << 2 * (sum - dp.get(0, n + 1)) << endl;
    return 0;
}