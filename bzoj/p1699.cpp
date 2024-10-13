#include <bits/stdc++.h>

using namespace std;

template<typename T> class SparseTable {
    public:
        SparseTable(const vector<T> &v, function<T(const T &, const T &)> _op=defaultFunc) {
            op = _op;
            n = v.size();
            assert(n > 0);
            f.resize(n, vector<T>(LOG2(n) + 1));
            for (int i = 0; i < n; ++i) f[i][0] = v[i];
            for (int j = 1; (1 << j) <= n; ++j) {
                for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                    f[i][j] = op(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        T get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = LOG2(r - l + 1);
            return op(f[l][k], f[r - (1 << k) + 1][k]);
        }
        
        // min;max;gcd;...
        static T defaultFunc(const T &a, const T &b) {
            return min(a, b);
        }
    private:
        int n;
        vector<vector<T>> f;

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }

        function<T(const T &, const T &)> op;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    SparseTable STMin(h);
    function<int(const int &, const int &)> maxFunc = [&](const int &a, const int &b) {
        return max(a, b);
    };
    SparseTable STMax(h, maxFunc);
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        cout << STMax.get(l, r) - STMin.get(l, r) << endl;
    }
    return 0;
}

