#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    vector<int> p(n, -1), sum(n, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            p[i] = p[i - 1];
            sum[i] = sum[i - 1] + (s[i] == '0');
        } else {
            sum[i] = (s[i] == '0');
        }
        if (s[i] == '0') p[i] = i;
    }
    function<bool(int)> check = [&](int len) {
        vector<vector<int>> f(n, vector<int>(k + 1, n + 5));
        for (int i = 0; i < n; ++i) {
            f[i][0] = 0;
            if (i == len - 1) f[i][1] = sum[i];
            for (int j = 1; j <= k; ++j) {
                if (i > 0) f[i][j] = min(f[i][j], f[i - 1][j]);
                if (i - len >= 0 && p[i - len] - 1 >= 0) {
                    f[i][j] = min(f[i][j], f[p[i - len] - 1][j - 1] + sum[i] - sum[i - len]);
                }
            }
        }
        return f[n - 1][k] <= m;
    };
    int ans = -1;
    int l = 1, r = (n - k + 1) / k;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}

