#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<vector<int>> G(n);
    vector<int> d(n, 0);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if (a[x] < a[y]) {
            G[x].push_back(y);
            ++d[y];
        }
        if (a[x] > a[y]) {
            G[y].push_back(x);
            ++d[x];
        }
    }
    vector<int> f(n, 1);
    int ans = 1;
    queue<int> Q;
    for (int i = 0; i < n; ++i) {
        if (d[i] == 0) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        ans = max(ans, f[u]);
        Q.pop();
        for (int i = 0; i < (int)G[u].size(); ++i) {
            int v = G[u][i];
            f[v] += f[u];
            --d[v];
            if (d[v] == 0) {
                Q.push(v);
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

