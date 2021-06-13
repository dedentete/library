// https://github.com/tsutaj/cpp_library/blob/master/math/math_005_matrix_mod2.cpp
struct BinaryMatrix {
    static constexpr int MAX = 2000;

    using mat = vector<bitset<MAX>>;

    int h, w;
    mat A;

    BinaryMatrix(int h, int w) : h(h), w(w), A(h) {}
    BinaryMatrix(mat A) : A(A) {}

    const bitset<MAX> &operator[](int i) const {
        return A[i];
    }

    bitset<MAX> &operator[](int i) {
        return A[i];
    }

    BinaryMatrix T(const BinaryMatrix &A) {
        int h = A.h, w = A.w;
        BinaryMatrix B(w, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                B[j][i] = A[i][j];
            }
        }
        return B;
    }

    BinaryMatrix &operator+=(const BinaryMatrix &B) {
        assert(h == B.h and w == B.w);
        for (int i = 0; i < h; i++) A[i] ^= B[i];
        return *this;
    }

    BinaryMatrix &operator-=(const BinaryMatrix &B) {
        return (*this += B);
    }

    BinaryMatrix &operator*=(const BinaryMatrix &B) {
        assert(w == B.h);
        BinaryMatrix res(h, B.w), C = T(B);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < B.w; j++) {
                res[i][j] = (A[i] & C[j]).count() % 2;
            }
        }
        return (*this = res);
    }

    BinaryMatrix operator+(const BinaryMatrix &B) {
        return (BinaryMatrix(*this) += B);
    }

    BinaryMatrix operator-(const BinaryMatrix &B) {
        return (BinaryMatrix(*this) -= B);
    }

    BinaryMatrix operator*(const BinaryMatrix &B) {
        return (BinaryMatrix(*this) *= B);
    }

    bool operator==(const BinaryMatrix &B) const {
        if (h != B.h or w != B.w) return false;
        for (int i = 0; i < h; i++)
            if (A[i] != B[i]) return false;
        return true;
    }

    bool operator!=(const BinaryMatrix &B) const {
        return !(*this == B);
    }

    BinaryMatrix identity(int n) {
        BinaryMatrix E(n, n);
        for (int i = 0; i < n; i++) E[i][i] = 1;
        return E;
    }

    BinaryMatrix pow(long long n) {
        BinaryMatrix B(A), C = identity(h);
        while (n > 0) {
            if (n & 1) C *= B;
            B *= B;
            n >>= 1;
        }
        return C;
    }

    void gauss(bool augmented = false) {
        int rank = 0;
        for (int i = 0; i < w; i++) {
            int idx = -1;
            for (int j = rank; j < h - augmented; j++) {
                if (A[j][i]) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) {
                continue;
            }
            swap(A[rank], A[idx]);
            for (int j = rank + 1; j < h; j++) {
                if (A[j][i]) {
                    A[j] ^= A[rank];
                }
            }
            rank++;
        }
    }

    // Ax = b
    void equation(vector<int> b) {
        bitset<MAX> bit;
        for (int i = 0; i < w; i++) {
            bit[i] = b[i];
        }
        A.emplace_back(bit);
        h++;
        gauss(true);
    }
};