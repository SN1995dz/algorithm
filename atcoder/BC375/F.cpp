#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(m), b(m), c(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        --a[i], --b[i];
    }
    vector<bool> ok(m, true);
    vector<int> op(q), x(q), y(q);
    vector<long long> ans;
    for (int i = 0; i < q; ++i) {
        cin >> op[i];
        if (op[i] == 1) {
            cin >> x[i];
            --x[i];
            ok[x[i]] = false;
        } else {
            cin >> x[i] >> y[i];
            --x[i], --y[i];
        }
    }
    const long long INF = 1e18;
    vector<vector<long long>> f(n, vector<long long>(n, INF));
    for (int i = 0; i < n; ++i) f[i][i] = 0;
    for (int i = 0; i < m; ++i) {
        if (ok[i]) {
            f[a[i]][b[i]] = c[i];
            f[b[i]][a[i]] = c[i];
        }
    }
    for (int i = 0; i < n; ++i) f[i][i] = 0;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    for (int i = q - 1; i >= 0; --i) {
        if (op[i] == 1) {
            int X = a[x[i]], Y = b[x[i]], Z = c[x[i]];
            for (int xx = 0; xx < n; ++xx) {
                for (int yy = 0; yy < n; ++yy) {
                    f[xx][yy] = min(f[xx][yy], f[xx][X] + f[Y][yy] + Z);
                    f[xx][yy] = min(f[xx][yy], f[xx][Y] + f[X][yy] + Z);
                }
            }
        } else {
            ans.push_back(f[x[i]][y[i]]);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (ans[i] == INF) cout << -1 << endl;
        else cout << ans[i] << endl;
    }
    return 0;
}

