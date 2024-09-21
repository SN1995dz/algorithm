#include <bits/stdc++.h>

using namespace std;

class DSU {
    public:
        explicit DSU(int n) : _n(n), parent_or_size(n + n, -1) {
            for (int i = 0; i < n; ++i) {
                parent_or_size[i] = n + i;
            }
        }

        int merge(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
            if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            return x;
        }

        bool same(int a, int b) {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            return leader(a) == leader(b);
        }

        void move(int a, int b) {
            // a move to b
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return;
            ++parent_or_size[x];
            --parent_or_size[y];
            parent_or_size[a] = y;
        }

        int leader(int a) {
            assert(0 <= a && a < _n + _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }
    private:
        int _n;
        // root node: -1 * component size; 0 is abandoned
        // otherwise: parent
        vector<int> parent_or_size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> x(n), y(n);
        vector<int> z(n);
        vector<long long> a;
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i] >> z[i];
            a.push_back(x[i]);
            a.push_back(y[i]);
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        function<int(long long)> find = [&](long long v) {
            return lower_bound(a.begin(), a.end(), v) - a.begin();
        };
        int m = a.size();
        DSU d(m);
        for (int i = 0; i < n; ++i) {
            if (z[i] == 1) {
                d.merge(find(x[i]), find(y[i]));
            }
        }
        bool ans = true;
        for (int i = 0; i < n; ++i) {
            if (z[i] == 0) {
                if (d.same(find(x[i]), find(y[i]))) {
                    ans = false;
                    break;
                }
            }
        }
        if (ans) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}

