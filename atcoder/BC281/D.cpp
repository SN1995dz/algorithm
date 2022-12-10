#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, d;
    cin >> n >> m >> d;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    const long long INF = 1e12;
    vector f(n + 1, vector(m + 1, vector<long long>(d, -INF)));
    f[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k < d; ++k) {
                f[i][j][k] = f[i - 1][j][k];
                if (j > 0) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][(k + d - a[i - 1] % d) % d] + a[i - 1]);
            }
        }
    }
    if (f[n][m][0] < 0) cout << -1 << endl;
    else cout << f[n][m][0] << endl;
    return 0;
}

