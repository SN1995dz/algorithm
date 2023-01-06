#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> col(n, -1);
    int cnt = 0;
    bool flag = true;
    int b = 0, w = 0;
    function<void(int, int)> dfs = [&](int u, int c) {
        col[u] = c;
        if (c == 0) ++b;
        else ++w;
        ++cnt;
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            if (col[v] != -1) {
                if (col[v] != (c ^ 1)) {
                    flag = false;
                    return;
                }
                continue;
            }
            dfs(v, c ^ 1);
            if (flag == false) return;
        }
    };
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        if (col[i] == -1) {
            int last = cnt;
            b = 0, w = 0;
            dfs(i, 0);
            if (flag == false) break;
            ans += (long long)w * b;
            ans += (long long)last * (w + b);
        }
    }
    ans -= m;
    if (flag == false) cout << "0" << endl;
    else cout << ans << endl;
    return 0;
}

