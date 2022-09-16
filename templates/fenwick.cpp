#include <bits/stdc++.h>

using namespace std;

template <typename T> class fenwick {
    public:
        vector<T> fenw;
        int n;

        fenwick(int _n) : n(_n) {
            fenw.resize(n);
        }

        void modify(int x, T v) {
            while (x < n) {
                fenw[x] += v;
                x |= (x + 1);
            }
        }

        T get(int x) {
            T v{};
            while (x >= 0) {
                v += fenw[x];
                x = (x & (x + 1)) - 1;
            }
            return v;
        }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    fenwick<int> fenw(10);
    fenw.modify(0, 1);
    cout << fenw.get(3) << endl;
    return 0;
}

