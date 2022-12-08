#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    vector<int> s(n, 0);
    for (int i = 0; i < n - m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int a, c;
            cin >> a >> c;
            G[i].push_back(a - 1);
            s[a - 1] -= c;
        }
    }
    for (int i = n - m; i < n; ++i) {
        int c;
        cin >> c;
        s[i] += c;
    }
    vector<int> p;
    vector<int> sz(n);
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            dfs(v);
            sz[u] += sz[v];
        }
        p.push_back(u);
    };
    dfs(0);
    const int INF = 3e5;
    vector<vector<int>> f(n + 1, vector<int>(m + 1, -INF));
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        int idx = p[i - 1];
        int ok = 0;
        if (idx >= n - m) ok = 1;
        for (int j = 0; j <= m; ++j) {
            f[i][j] = f[i - sz[idx]][j];
            if (j - ok >= 0) f[i][j] = max(f[i][j], f[i - 1][j - ok] + s[idx]);
        }
    }
    int ans = 0;
    for (int j = m; j > 0; --j) {
        if (f[n][j] >= 0) {
            ans = j;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}

