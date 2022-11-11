#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector f = vector(n, vector(n, vector<long long>(2, -1)));
    function<long long(int, int, int)> dp = [&](int l, int r, int c) {
        if (l == r) return 0LL;
        if (f[l][r][c] != -1) return f[l][r][c];
        if (c == 0) {
            long long x = dp(l + 1, r, 0);
            long long y = dp(l + 1, r, 1);
            f[l][r][c] = min(x + min(abs(a[l + 1] - a[l]), d - abs(a[l + 1] - a[l])), y + min(abs(a[r] - a[l]), d - abs(a[r] - a[l])));
        } else {
            long long x = dp(l, r - 1, 0);
            long long y = dp(l, r - 1, 1);
            f[l][r][c] = min(x + min(abs(a[l] - a[r]), d - abs(a[l] - a[r])), y + min(abs(a[r - 1] - a[r]), d - abs(a[r - 1] - a[r])));
        }
        return f[l][r][c];
    };
    long long ans = min(dp(0, n - 1, 0) + min(a[0], d - a[0]), dp(0, n - 1, 1) + min(a[n - 1], d - a[n - 1]));
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

