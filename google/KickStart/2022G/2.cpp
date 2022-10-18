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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> s(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        s[i + 1] = s[i] + a[i];
    }
    vector<long long> b(n + 2, 0);
    for (int i = 0; i <= n; ++i) {
        b[i + 1] = b[i] + s[i];
    }
    sparse_table<int> st(s);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        int l = i, r = n, res = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (st.get(i, mid) - s[i - 1] >= 0) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (res == -1) continue;
        ans += b[res + 1] - b[i] - (long long)(res - i + 1) * s[i - 1];
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

