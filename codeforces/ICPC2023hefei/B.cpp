#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    const int MOD = 998244353;
    int n;
    cin >> n;
    vector<int> a(n);
    int m = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == 0) {
            --i;
            --n;
            continue;
        }
        m += a[i];
    }
    vector<vector<int>> c(m + m, vector<int>(m + m, 0));
    for (int i = 0; i < m + m; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }
    vector<vector<int>> f(n, vector<int>(m + 1, 0));
    f[0][a[0]] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m; ++j) { // m -> psum[i]
            for (int k = 0; k <= a[i]; ++k) {
                if (j - (a[i] - k) > 0) {
                    if (k == 0) {
                        f[i][j] = (f[i][j] + f[i - 1][j - (a[i] - k)]) % MOD;
                    } else {
                        for (int l = j - (a[i] - k); l <= m; ++l) {
                            int bars = l - (j - (a[i] - k)) + 1, stars = k - 1;
                            f[i][j] = (f[i][j] + (long long)f[i - 1][l] * c[stars + bars - 1][bars - 1] % MOD) % MOD;
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; ++j) {
        ans = (ans + f[n - 1][j]) % MOD;
    }
    cout << ans << endl;
    return 0;
}

