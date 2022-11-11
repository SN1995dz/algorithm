#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    vector<vector<int>> a(2 * n, vector<int>(2 * m, -1));
    const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
    const char dc[4] = {'E', 'S', 'W', 'N'};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '*') {
                int xx = i * 2, yy = j * 2;
                a[xx][yy] = 0;
                a[xx][yy + 1] = 1;
                a[xx + 1][yy + 1] = 2;
                a[xx + 1][yy] = 3;
            }
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    function<void(int, int, int)> dfs = [&](int x, int y, int d) {
        visited[x][y] = true;
        int xx = x * 2, yy = y * 2;
        if (d == 0) {
            a[xx][yy - 1] = 0;
            a[xx + 1][yy] = 2;
        }
        if (d == 1) {
            a[xx - 1][yy + 1] = 1;
            a[xx][yy] = 3;
        }
        if (d == 2) {
            a[xx][yy + 1] = 0;
            a[xx + 1][yy + 2] = 2;
        }
        if (d == 3) {
            a[xx + 2][yy] = 3;
            a[xx + 1][yy + 1] = 1;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && visited[nx][ny] == false && s[nx][ny] == '*') {
                dfs(nx, ny, i);
            }
        }
    };
    dfs(0, 0, -1);
    bool ok = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '*' && visited[i][j] == false) {
                ok = false;
            }
        }
    }
    if (ok) {
        int x = 0, y = 0;
        string ans;
        do {
            ans.push_back(dc[a[x][y]]);
            int nx = x + dx[a[x][y]], ny = y + dy[a[x][y]];
            x = nx, y = ny;
        } while (x != 0 || y != 0);
        cout << ans << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; ++Case) {
        cout << "Case #" << Case << ": ";
        solve();
    }
    return 0;
}

