#include <bits/stdc++.h>

using namespace std;

template<typename T> class sparse_table {
    public:
        int n;
        vector<vector<T>> f;
        vector<vector<int>> g;

        inline int LOG2(unsigned int x) {
            return 31 - __builtin_clz(x);
        }

        sparse_table(const vector<T> &v) {
            n = v.size();
            assert(n > 0);
            f.resize(n, vector<T>(LOG2(n) + 1));
            g.resize(n, vector<int>(LOG2(n) + 1));
            for (int i = 0; i < n; ++i) {
                f[i][0] = v[i];
                g[i][0] = i;
            }
            for (int j = 1; (1 << j) <= n; ++j) {
                for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                    if (f[i][j - 1] < f[i + (1 << (j - 1))][j - 1]) {
                        f[i][j] = f[i][j - 1];
                        g[i][j] = g[i][j - 1];
                    } else {
                        f[i][j] = f[i + (1 << (j - 1))][j - 1];
                        g[i][j] = g[i + (1 << (j - 1))][j - 1];
                    }
                }
            }
        }

        T get(int l, int r) {
            assert(0 <= l && l <= r && r < n);
            int k = LOG2(r - l + 1);
            if (f[l][k] < f[r - (1 << k) + 1][k]) return g[l][k];
            return g[r - (1 << k) + 1][k];
        }
};

int main() {
    ios::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
    int n, m, rt;
    //cin >> n >> m >> rt;
    scanf("%d%d%d", &n, &m, &rt);
    --rt;
    vector<vector<int>> G(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        //cin >> x >> y;
        scanf("%d%d", &x, &y);
        --x, --y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    vector<int> fi(n);
    vector<int> vs, depth;
    function<void(int, int, int)> dfs = [&](int u, int p, int d) {
        fi[u] = vs.size();
        vs.push_back(u);
        depth.push_back(d);
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            if (v == p) continue;
            dfs(v, u, d + 1);
            vs.push_back(u);
            depth.push_back(d);
        }
    };
    dfs(rt, -1, 0);
    sparse_table<int> st(depth);
    auto lca = [&](int u, int v) {
        return vs[st.get(min(fi[u], fi[v]), max(fi[u], fi[v]))];
    };
    while (m--) {
        int x, y;
        //cin >> x >> y;
        scanf("%d%d", &x, &y);
        --x, --y;
        //cout << lca(x, y) + 1 << endl;
        printf("%d\n", lca(x, y) + 1);
    }
    return 0;
}

