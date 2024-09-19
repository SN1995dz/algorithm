#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int l, n, m;
        cin >> l >> n >> m;
        vector<int> a(l);
        for (int i = 0; i < l; ++i) cin >> a[i];
        const int INF = 1e9;
        vector<int> pos(n * m + 1, INF);
        for (int i = 0; i < l; ++i) {
            if (pos[a[i]] != INF) {
                l = i;
                break;
            }
            pos[a[i]] = i;
        }
        vector<vector<int>> b(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> b[i][j];
            }
        }
        if (n > m) {
            swap(n, m);
            vector<vector<int>> c(n, vector<int>(m));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    c[i][j] = b[j][i];
                }
            }
            swap(b, c);
        }
        // vector<vector<vector<int>>> f(n, vector<vector<int>>(m, vector<int>(2, -1)));
        vector<vector<vector<int>>> f(2, vector<vector<int>>(n, vector<int>(m, -1)));
        function<int(int, int, int)> check = [&](int x, int y, int z) {
            // if (f[x][y][z] != -1) return f[x][y][z];
            if (f[z][x][y] != -1) return f[z][x][y];
            int res = INF;
            if (x < n - 1) res = min(res, check(x + 1, y, z));
            if (y < m - 1) res = min(res, check(x, y + 1, z));
            int ind = pos[b[x][y]];
            if (x == n - 1 || y == m - 1 || check(x + 1, y + 1, z ^ 1) > ind + 1) res = min(res, ind);
            // return f[x][y][z] = res;
            return f[z][x][y] = res;
        };
        if (check(0, 0, 0) == 0) cout << "T" << endl;
        else cout << "N" << endl;
    }
    return 0;
}

