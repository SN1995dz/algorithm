#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n + 1);
    vector<int> s(n + 1);
    s[n] = 0;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k >> s[i];
        if (k != 0) {
            G[k - 1].push_back(i);
        } else {
            G[n].push_back(i);
        }
    }
    vector<int> sz(n + 1);
    vector<int> S;
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            dfs(v);
            sz[u] += sz[v];
        }
        S.push_back(u);
    };
    dfs(n);
    vector<vector<int>> f(n + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= n + 1; ++i) {
        int idx = S[i - 1];
        for (int j = 1; j <= m + 1; ++j) {
            f[i][j] = max(f[i - sz[idx]][j], f[i - 1][j - 1] + s[idx]);
        }
    }
    cout << f[n + 1][m + 1] << endl;
    return 0;
}

