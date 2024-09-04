#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> d(n, 0);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            ++d[u];
            ++d[v];
        }
        string s;
        cin >> s;
        if (s[0] == '?') {
            int a = 0, b = 0, c = 0, x = 0;
            for (int i = 1; i < n; ++i) {
                if (d[i] == 1) {
                    if (s[i] == '?') ++a;
                    if (s[i] == '0') ++b;
                    if (s[i] == '1') ++c;
                } else {
                    if (s[i] == '?') ++x;
                }
            }
            if (b == c) {
                if (x & 1) cout << max(b, c) + (a + 1) / 2 << endl;
                else cout << max(b, c) + a / 2 << endl;
            } else {
                cout << max(b, c) + a / 2 << endl;
            }
        } else {
            int ans = 0, cnt = 1;
            for (int i = 1; i < n; ++i) {
                if (d[i] == 1) {
                    if (s[i] == '?') {
                        ans += cnt & 1;
                        ++cnt;
                    } else {
                        if (s[i] != s[0]) ++ans;
                    }
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}

