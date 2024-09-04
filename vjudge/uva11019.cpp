#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long pBase = 269, qBase = 271;
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<string> s(n);
        for (int i = 0; i < n; ++i) cin >> s[i];
        vector<unsigned long long> p(m + 1), q(n + 1);
        p[0] = q[0] = 1;
        for (int i = 1; i <= m; ++i) p[i] = p[i - 1] * pBase;
        for (int i = 1; i <= n; ++i) q[i] = q[i - 1] * qBase;
        vector<vector<unsigned long long>> a(n + 1, vector<unsigned long long>(m + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i + 1][j + 1] = a[i + 1][j] * pBase + s[i][j];
            }
        }
        for (int j = 0; j < m; ++j) {
            for (int i = 1; i < n; ++i) {
                a[i + 1][j + 1] = a[i][j + 1] * qBase + a[i + 1][j + 1];
            }
        }
        int x, y;
        cin >> x >> y;
        vector<string> t(x);
        for (int i = 0; i < x; ++i) cin >> t[i];
        vector<vector<unsigned long long>> b(x + 1, vector<unsigned long long>(y + 1, 0));
         for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                b[i + 1][j + 1] = b[i + 1][j] * pBase + t[i][j];
            }
        }
        for (int j = 0; j < y; ++j) {
            for (int i = 1; i < x; ++i) {
                b[i + 1][j + 1] = b[i][j + 1] * qBase + b[i + 1][j + 1];
            }
        }
        auto query = [&](int r, int c, int R, int C) {
            return a[R][C] - a[R][c - 1] * p[C - c + 1] - a[r - 1][C] * q[R - r + 1] + a[r - 1][c - 1] * p[C - c + 1] * q[R - r + 1];
        };
        int ans = 0;
        for (int i = x; i <= n; ++i) {
            for (int j = y; j <= m; ++j) {
                if (b[x][y] == query(i - x + 1, j - y + 1, i, j)) ++ans;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

