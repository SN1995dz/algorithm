#include <bits/stdc++.h>

using namespace std;

template<typename T> class sparse_table {
    public:
        int n;
        vector<vector<T>> f;

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }

        sparse_table(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            f.resize(n, vector<T>(LOG2(n) + 1));
            for (int i = 0; i < n; ++i) f[i][0] = v[i];
            for (int j = 1; (1 << j) <= n; ++j) {
                for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                    //min or max
                    f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        T get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = LOG2(r - l + 1);
            //min or max
            return min(f[l][k], f[r - (1 << k) + 1][k]);
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sparse_table<int> st(a);
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << st.get(l, r) << endl;
    }
    return 0;
}

