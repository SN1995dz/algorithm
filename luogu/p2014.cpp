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
    vector<vector<int>> f(n + 1, vector<int>(m + 2, -1));
    function<int(int, int)> dp = [&](int u, int w) {
        if (w == 0) return 0;
        if (w == 1) return s[u];
        if (f[u][w] != -1) return f[u][w];
        vector<int> g(w, 0);
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            for (int j = w - 1; j >= 0; --j) {
                for (int k = j; k >= 0; --k) {
                    g[j] = max(g[j], g[j - k] + dp(v, k));
                }
            }
        }
        return f[u][w] = g[w - 1] + s[u];
    };
    cout << dp(n, m + 1) << endl;
    return 0;
}

