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
    int n;
    cin >> n;
    vector<vector<long long>> a(n, vector<long long>(n));
    vector<pair<int, int>> p;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> a[i][j];
            if (i != j) p.push_back(make_pair(i, j));
        }
    }
    sort(p.begin(), p.end(), [&](const pair<int, int> &x, const pair<int, int> &y){
        return a[x.first][x.second] > a[y.first][y.second];
    });
    dsu d(n);
    vector<vector<int>> G(n);
    int cnt = 0;
    for (auto &e : p) {
        if (d.same(e.first, e.second)) continue;
        d.merge(e.first, e.second);
        G[e.first].push_back(e.second);
        G[e.second].push_back(e.first);
        ++cnt;
        if (cnt == n - 1) break;
    }
    vector<int> U, V, W;
    vector<int> sz(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
        sz[u] = 1;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            if (v == fa) continue;
            dfs(v, u);
            sz[u] += sz[v];
            U.push_back(u + 1);
            V.push_back(v + 1);
            if (u >= v) {
                W.push_back((a[u][u] - a[u][v]) / sz[v]);
            } else {
                W.push_back((a[u][u] - a[v][u]) / sz[v]);
            }
        }
    };
    dfs(0, -1);
    for (int i = 0; i < (int)U.size(); ++i) cout << U[i] << " " << V[i] << " " << W[i] << endl;
    return 0;
}

