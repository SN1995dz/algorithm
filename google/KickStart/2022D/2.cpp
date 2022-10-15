#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) cin >> b[i];
    vector l(m, vector<int>(2501, -1));
    for (int i = 0; i < m; ++i) {
        if (i == 0) {
            l[i][b[i]] = i;
            continue;
        }
        for (int j = 1; j <= 2500; ++j) {
            if (j == b[i]) l[i][j] = i;
            else l[i][j] = l[i - 1][j];
        }
    }
    vector r(m, vector<int>(2501, -1));
    for (int i = m - 1; i >= 0; --i) {
        if (i == m - 1) {
            r[i][b[i]] = i;
            continue;
        }
        for (int j = 1; j <= 2500; ++j) {
            if (j == b[i]) r[i][j] = i;
            else r[i][j] = r[i + 1][j];
        }
    }
    const int INF = 1e9;
    vector f(n, vector<int>(m, INF));
    for (int i = 0; i < m; ++i) {
        if (b[i] == a[0]) {
            f[0][i] = 0;
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] < INF) {
                int tgt = a[i + 1];
                if (l[j][tgt] != -1) f[i + 1][l[j][tgt]] = min(f[i + 1][l[j][tgt]], f[i][j] + j - l[j][tgt]);
                if (r[j][tgt] != -1) f[i + 1][r[j][tgt]] = min(f[i + 1][r[j][tgt]], f[i][j] + r[j][tgt] - j);
            }
        }
    }
    int ans = INF;
    for (int j = 0; j < m; ++j) ans = min(ans, f[n - 1][j]);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

