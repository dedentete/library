/*
    1-indexed であることに注意 !! 
*/
template <typename T>
struct BIT{
    vector<T> dat;

    BIT(int sz) : dat(sz + 1, 0) {}

    T sum(int a){
        T res = 0;
        for(int i = a; i > 0; i -= (i & (-i))) res += dat[i];
        return res;
    }

    T sum(int a, int b){
        return sum(b - 1) - sum(a - 1);
    }

    void add(int k, T x){
        for(int i = k; i <= dat.size(); i += (i & (-i))) dat[i] += x;
    }
};