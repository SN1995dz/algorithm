#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    string name = "narek";
    set<char> S;
    S.insert('n');
    S.insert('a');
    S.insert('r');
    S.insert('e');
    S.insert('k');
    const int INF = 1e9;
    while (T--) {
        int n, m, ans = 0;
        cin >> n >> m;
        vector<string> s(n);
        for (int i = 0; i < n; ++i) cin >> s[i];
        vector<vector<int>> f(n + 1, vector<int>(5, -INF));
        f[0][0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < 5; ++k) {
                if (f[i][k] != -INF) {
                    f[i + 1][k] = max(f[i + 1][k], f[i][k]);
                    int ti = k, scoreN = 0, scoreC = 0;
                    for (int j = 0; j < m; ++j) {
                        if (s[i][j] == name[ti]) {
                            ++ti;
                            if (ti == 5) {
                                scoreN += 5;
                                ti = 0;
                            }
                        } else {
                            if (S.count(s[i][j])) {
                                ++scoreC;
                            }
                        }
                    }
                    f[i + 1][ti] = max(f[i + 1][ti], f[i][k] + scoreN - scoreC);
                }
            }
        }
        for (int k = 0; k < 5; ++k) {
            ans = max(ans, f[n][k] - k);
        }
        cout << ans << endl;
    }
    return 0;
}

