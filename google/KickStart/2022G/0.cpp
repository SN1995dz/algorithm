#include <bits/stdc++.h>

using namespace std;

void solve() {
    int m, n, p;
    cin >> m >> n >> p;
    vector<vector<int>> s(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> s[i][j];
        }
    }
    int ans = 0;
    for (int j = 0; j < n; ++j) {
        int tmp = -1;
        for (int i = 0; i < m; ++i) {
            tmp = max(tmp, s[i][j]);
        }
        ans += tmp - s[p - 1][j];
    }
    cout << ans << endl;
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

