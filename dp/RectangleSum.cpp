template <typename T>
struct RectangleSum {
    vector<vector<T>> sum;

    RectangleSum(int h, int w) {
        init(h, w);
    }

    void init(int h, int w) {
        sum.resize(h + 1, vector<T>(w + 1, 0));
    }

    void add(int y, int x, T val) {
        y++;
        x++;
        sum[y][x] += val;
    }

    void build() {
        for (int i = 1; i < sum.size(); i++) {
            for (int j = 1; j < sum[i].size(); j++) {
                sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
            }
        }
    }

    T getsum(int top, int left, int bottom,
             int right) {  //[top, bottom), [left, right)
        return sum[bottom][right] - sum[bottom][left] - sum[top][right] +
               sum[top][left];
    }
};