#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool flag = true;
            for (int k = 0; k < m; ++k) {
                if (s[i][k] == 'x' && s[j][k] == 'x') {
                    flag = false;
                    break;
                }
            }
            if (flag) ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}

