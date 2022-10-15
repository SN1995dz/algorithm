#include <bits/stdc++.h>

using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.length(), m = t.length();
    int ans = -1;
    for (int i = 0, j = 0; i < m; ++i) {
        if (t[i] == s[j]) {
            ++j;
            if (j == n) {
                ans = m - n;
                break;
            }
        }
    }
    if (ans == -1) cout << "IMPOSSIBLE" << endl;
    else cout << ans << endl;
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

