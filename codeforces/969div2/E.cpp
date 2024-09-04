#include <bits/stdc++.h>

using namespace std;

struct dsu {
    public:
        dsu() : _n(0) {}
        explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

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
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        long long w;
        cin >> n >> w;
        vector<int> p(n, -1);
        vector<vector<int>> G(n);
        for (int i = 1; i < n; ++i) {
            cin >> p[i];
            --p[i];
            G[p[i]].push_back(i);
        }
        vector<int> sz(n, 0);
        function<void(int)> dfs = [&](int u) {
            sz[u] = 1;
            for (int i = 0; i < (int)G[u].size(); ++i) {
                int v = G[u][i];
                dfs(v);
                sz[u] += sz[v];
            }
        };
        dfs(0);
        dsu d(n);
        set<pair<int, int>> S;
        long long sum = 0;
        for (int i = 0; i < n - 1; ++i) {
            int x;
            long long y;
            cin >> x >> y;
            --x;
            d.merge(p[x], x);
            if (d.same(x, x - 1)) {
                S.insert(make_pair(x - 1, x));
            }
            int tmp = x + sz[x];
            if (tmp == n) tmp = 0;
            if (d.same(x + sz[x] - 1, tmp)) {
                S.insert(make_pair(min(x + sz[x] - 1, tmp), max(x + sz[x] - 1, tmp)));
            }
            sum += y;
            cout << sum * 2 + (n - (int)S.size()) * (w - sum) << " ";
        }
        cout << endl;
    }
    return 0;
}

