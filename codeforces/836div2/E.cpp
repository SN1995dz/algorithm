#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    const int MOD = 1e9 + 7;
    while (T--) {
        int n, m, h;
        cin >> n >> m >> h;
        vector a(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
            }
        }
        int ans = 1;
        vector<int> f(m), d(m, 0);
        for (int i = 0; i < m; ++i) f[i] = i;
        vector<int> p(n, -1);
        function<int(int)> find = [&](int x) {
            if (f[x] == x) return f[x];
            int par = f[x];
            f[x] = find(f[x]);
            d[x] = (d[par] + d[x]) % h;
            return f[x];
        };
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] != -1) {
                    if (p[i] != -1) {
                        int x = find(j), y = find(p[i]);
                        if (x != y) {
                            f[x] = y;
                            d[x] = ((d[p[i]] + h - d[j]) % h + (a[i][p[i]] - a[i][j] + h) % h) % h;
                        } else {
                            if ((d[j] + h - d[p[i]]) % h != (a[i][p[i]] - a[i][j] + h) % h) {
                                ans = 0;
                            }
                        }
                    }
                    p[i] = j;
                }
            }
        }
        if (ans == 0) {
            cout << 0 << endl;
            continue;
        }
        vector<bool> flag(m, false);
        for (int j = 0; j < m; ++j) {
            if (a[0][j] != -1) {
                flag[find(j)] = true;
            }
        }
        for (int j = 0; j < m; ++j) {
            if (find(j) == j && flag[j] == false) {
                ans = (long long)ans * h % MOD;
            }
        }
        vector<bool> mark(n, false);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] != -1) {
                    mark[i] = true;
                }
            }
        }
        for (int i = 1; i < n; ++i) {
            if (mark[i] == false) {
                ans = (long long)ans * h % MOD;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

