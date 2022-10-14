#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        int n, q;
        cin >> n >> q;
        vector<vector<int>> G(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for (int i = 0; i < q; ++i) {
            int x;
            cin >> x;
        }
        vector<int> d(n, -1);
        vector<int> cnt(n, 0);
        d[0] = 0;
        cnt[0] = 1;
        function<void(int, int)> dfs = [&](int u, int fa) {
            for (int i = 0; i < (int)G[u].size(); ++i) {
                int v = G[u][i];
                if (v == fa) continue;
                d[v] = d[u] + 1;
                ++cnt[d[v]];
                dfs(v, u);
            }
        };
        dfs(0, -1);
        int ans = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += cnt[i];
            if (sum <= q) {
                ans = sum;
            } else {
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

