#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> m >> n;
    vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(m + 1, vector<int>(m + 1, 0)));
    f[0][0][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= j; ++k) {
                for (int l = 1; l <= k; ++l) {
                    f[i][j][k] += f[i - 1][j - k][l];
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i) ans += f[n][m][i];
    cout << ans << endl;
    return 0;
}

