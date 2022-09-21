#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        vector<vector<int>> ds(n, vector<int>(n, INF));
        vector<vector<int>> dl(n, vector<int>(n, INF));
        while (m--) {
            int x, y, z;
            string SL;
            cin >> x >> y >> z >> SL;
            --x, --y;
            if (SL[0] == 'S') {
                ds[x][y] = min(ds[x][y], z);
                ds[y][x] = min(ds[y][x], z);
            } else {
                dl[x][y] = min(dl[x][y], z);
                dl[y][x] = min(dl[x][y], z);
            }
        }
        for (int k = 0; k < n; ++k) {
            ds[k][k] = 0;
            dl[k][k] = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
                    dl[i][j] = min(dl[i][j], dl[i][k] + dl[k][j]);
                }
            }
        }
        int r;
        cin >> r;
        vector<vector<int>> f(r, vector<int>(n, INF));
        vector<int> a(r);
        for (int i = 0; i < r; ++i) {
            cin >> a[i];
            --a[i];
            if (i == 0) {
                f[i][a[i]] = 0;
                for (int j = 0; j < n; ++j) {
                    f[i][j] = min(f[i][j], ds[a[i]][j] + dl[j][a[i]]);
                }
            } else {
                for (int j = 0; j < n; ++j) {
                    for (int k = 0; k < n; ++k) {
                        if (j == k) f[i][j] = min(f[i][j], f[i - 1][k] + dl[a[i - 1]][a[i]]);
                        else f[i][j] = min((long long)f[i][j], (long long)f[i - 1][k] + dl[a[i - 1]][k] + ds[k][j] + dl[j][a[i]]);
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < n; ++i) ans = min(ans, f[r - 1][i]);
        cout << ans << endl;
    }
    return 0;
}

