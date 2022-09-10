#include <bits/stdc++.h>

using namespace std;

struct dsu {
    public:
        dsu() : _n(0) {}
        explicit dsu(int n) : _n(n), parent_or_size(n, -1){}

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

        int leader(int a) {
            assert(0 <= a && a < _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = leader(parent_or_size[a]);
        }

        int size(int a) {
            assert(0 <= a && a < _n);
            return -parent_or_size[leader(a)];
        }

        vector<vector<int>> groups() {
            vector<int> leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; ++i) {
                leader_buf[i] = leader(i);
                ++group_size[leader_buf[i]];
            }
            vector<vector<int>> result(_n);
            for (int i = 0; i < _n; ++i) {
                result[i].reserve(group_size[i]);
            }
            for (int i = 0; i < _n; ++i) {
                result[leader_buf[i]].push_back(i);
            }
            result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
            return result;
        }

    private:
        int _n;
        // root node: -1 * component size
        // otherwise: parent
        vector<int> parent_or_size;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, h, r;
        cin >> n >> h >> r;
        dsu d(n + 2);
        vector<int> x(n + 1), y(n + 1), z(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> x[i] >> y[i] >> z[i];
        }
        for (int i = 1; i <= n; ++i) {
            if (z[i] <= r) {
                d.merge(0, i);
            }
            if (h - z[i] <= r) {
                d.merge(n + 1, i);
            }
        }
        auto dist = [&](int i, int j) {
            return (long long)(x[i] - x[j]) * (x[i] - x[j]) + (long long)(y[i] - y[j]) * (y[i] - y[j]) + (long long)(z[i] - z[j]) * (z[i] - z[j]);
        };
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (dist(i, j) <= 4LL * r * r) {
                    d.merge(i, j);
                }
            }
        }
        if (d.same(0, n + 1)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}

