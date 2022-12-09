#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N, W;
    cin >> N >> W;
    vector<vector<int>> G(N + 1);
    for (int i = 1; i <= N; ++i) {
        int d;
        cin >> d;
        G[d].push_back(i);
    }
    vector<int> w(N + 1, 0), v(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> w[i];
    for (int i = 1; i <= N; ++i) cin >> v[i];
    vector<int> sz(N + 1);
    vector<int> p;
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
    vector<vector<int>> f(N + 2, vector<int>(W + 1, 0));
    for (int i = 1; i <= N + 1; ++i) {
        int idx = p[i - 1];
        for (int j = 0; j <= W; ++j) {
            f[i][j] = f[i - sz[idx]][j];
            if (j - w[idx] >= 0) {
                f[i][j] = max(f[i][j], f[i - 1][j - w[idx]] + v[idx]);
            }
        }
    }
    cout << f[N + 1][W] << endl;
    return 0;
}

