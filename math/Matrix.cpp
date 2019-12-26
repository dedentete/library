/*
    計算量...
    和, 差 : O(N ^ 2)
    積 : O(N ^ 3)
    行列累乗(N ^ K) : O(N ^ 3 log K)
*/
template <typename T>
struct Matrix{
    typedef vector<vector<T>> mat;

    mat A;

    Matrix() {}
    Matrix(int h, int w, T x = T(0)) : A(h, vector<T>(w, x) {}
    Matrix(mat A) : A(A) {}

    int size() const { return A.size(); }
    const vector<T> & operator[] (int i) const { return A[i]; }
    vector<T> & operator[] (int i) { return A[i]; }

    Matrix & operator += (const Matrix & B){
        assert(A.size() == B.size());
        assert(A[0].size() == B[0].size());
        for(int i = 0; i < A.size(); i++){
            for(int j = 0; j < A[0].size(); j++){
                A[i][j] += B[i][j];
            }
        }
        return *this;
    }

    Matrix & operator -= (const Matrix & B){
        assert(A.size() == B.size());
        assert(A[0].size() == B[0].size());
        for(int i = 0; i < A.size(); i++){
            for(int j = 0; j < A[0].size(); j++){
                A[i][j] -= B[i][j];
            }
        }
        return *this;
    }

    Matrix & operator *= (const Matrix & B){
        assert(A[0].size() == B.size());
        int h = A.size(), w = B[0].size();
        Matrix C(h, w);
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                for(int k = 0; k < B.size(); k++){
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        A.swap(C);
        return *this;
    }

    Matrix operator + (const Matrix & B) const { return (Matrix(*this) += B); }
    Matrix operator - (const Matrix & B) const { return (Matrix(*this) -= B); }
    Matrix operator * (const Matrix & B) const { return (Matrix(*this) *= B); }

    Matrix identity(int n){
        Matrix E(n, n);
        for(int i = 0; i < n; i++) E[i][i] = T(1);
        return E;
    }

    Matrix pow(long long n){
        Matrix B(A), C = identity(A.size());
        while(n > 0){
            if(n & 1) C *= B;
            B *= B;
            n >>= 1;
        }
        return C;
    }
};