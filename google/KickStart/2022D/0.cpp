#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    double ans = 0.0;
    sort(a.rbegin(), a.rend());
    for (int i = 0; i < m - 1; ++i) ans += a[i];
    for (int l = m - 1, r = n - 1; l <= r; ++l, --r) {
        if (l + 1 == r) {
            ans += (a[l] + a[r]) / 2.0;
        }
        if (l == r) ans += a[l];
    }
    cout << fixed << setprecision(6) << ans << endl;
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

