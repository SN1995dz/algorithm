#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    const int MOD = 1e9 + 7;
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
    f[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        vector<int> sum(i, 0);
        for (int j = 1; j <= i - 1; ++j) sum[j] = (sum[j - 1] + f[i - 1][j]) % MOD;
        for (int j = 1; j <= i; ++j) {
            int L, R;
            if (s[i - 2] == '<') {
                L = 1;
                R = j - 1;
            } else {
                L = j;
                R = i - 1;
            }
            if (L <= R) {
                f[i][j] = (sum[R] - sum[L - 1] + MOD) % MOD;
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= n; ++j) {
        ans = (ans + f[n][j]) % MOD;
    }
    cout << ans << endl;
    return 0;
}

