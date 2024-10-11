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
    private:
        int n;
        vector<vector<T>> f;

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }

        // min;max;gcd;...
        static T defaultFunc(const T &a, const T &b) {
            return max(a, b);
        }

        function<T(const T &, const T &)> op;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> y(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> y[i] >> r[i];
    }
    SparseTable<int> ST(r);
    int m;
    cin >> m;
    while (m--) {
        int Y, X;
        cin >> Y >> X;
        int curY = lower_bound(y.begin(), y.end(), Y) - y.begin();
        int curX = lower_bound(y.begin(), y.end(), X) - y.begin();
        bool notFoundY = false, notFoundX = false;
        if (curY == n || y[curY] != Y) notFoundY = true;
        if (curX == n || y[curX] != X) notFoundX = true;
        if (notFoundY && notFoundX) {
            cout << "maybe" << endl;
            continue;
        }
        if (notFoundY) {
            if (curY <= curX - 1 && ST.get(curY, curX - 1) >= r[curX]) cout << "false" << endl;
            else  cout << "maybe" << endl;
            continue;
        }
        if (notFoundX) {
            if (curY + 1 <= curX - 1 && ST.get(curY + 1, curX - 1) >= r[curY]) cout << "false" << endl;
            else cout << "maybe" << endl;
            continue;
        }
        if (r[curX] > r[curY]) {
            cout << "false" << endl;
            continue;
        }
        if (curY + 1 <= curX - 1 && ST.get(curY + 1, curX - 1) >= r[curX]) {
            cout << "false" << endl;
            continue;
        }
        if (curX - curY == X - Y) cout << "true" << endl;
        else cout << "maybe" << endl;
    }
    return 0;
}

