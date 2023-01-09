#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k, p;
    cin >> n >> k >> p;
    vector f = vector(2, vector(k + 1, vector(n + 1, vector<int>(n + 1, 0))));
    f[1][0][1][1] = 1;
    auto add = [&](int &x, int y) {
        x += y;
        if (x >= p) x -= p;
    };
    auto qsum = [&](int x1, int y1, int x2, int y2, vector<vector<int>> &g) {
        if (x2 < x1 || y2 < y1) return 0;
        return (((g[x2][y2] - g[x2][y1 - 1] + p) % p - g[x1 - 1][y2] + p) % p + g[x1 - 1][y1 - 1]) % p;
    };
    int cur = 0, pre = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= k; ++i) {
            for (int x = 1; x <= len - 1; ++x) {
                for (int y = 1; y <= len - 1; ++y) {
                    add(f[pre][i][x][y], f[pre][i][x][y - 1]);
                }
            }
            for (int y = 1; y <= len - 1; ++y) {
                for (int x = 1; x <= len - 1; ++x) {
                    add(f[pre][i][x][y], f[pre][i][x - 1][y]);
                }
            }
            for (int a = 1; a <= len; ++a) {
                for (int b = 1; b <= len; ++b) {
                    f[cur][i][a][b] = 0;
                    if (i > 0) {
                        add(f[cur][i][a][b], qsum(1, 1, a - 1, b - 1, f[pre][i - 1]));
                        add(f[cur][i][a][b], qsum(a, b, len - 1, len - 1, f[pre][i - 1]));
                    }
                    add(f[cur][i][a][b], qsum(1, b, a - 1, len - 1, f[pre][i]));
                    add(f[cur][i][a][b], qsum(a, 1, len - 1, b - 1, f[pre][i]));
                }
            }
        }
        swap(cur, pre);
    }
    int ans = 0;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            add(ans, f[pre][k][a][b]);
        }
    }
    cout << ans << endl;
    return 0;
}

