#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> a(n);
    vector<string> ans(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ans[i] = a[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int mn = min(i, j), mx = max(i, j);
            int t = min(mn, n - 1 - mx);
            if (t % 4 == 0) {
                ans[j][n - 1 - i] = a[i][j];
            } else if (t % 4 == 1) {
                ans[n - 1 - i][n - 1 - j] = a[i][j];
            } else if (t % 4 == 2) {
                ans[n - 1 - j][i] = a[i][j];
            } else if (t % 4 == 3) {
                ans[i][j] = a[i][j];
            }
        }
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << endl;
    return 0;
}

