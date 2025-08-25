#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int b = static_cast<int>(ceil(sqrt(n)));
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<vector<int>> f(b, vector<int>(b, 0));
    for (int j = 1; j < b; ++j) {
        for (int i = 1; i <= n; ++i) {
            f[j][i % j] += a[i];
        }
    }
    while (m--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        if (op[0] == 'A') {
            if (x >= b) {
                int ans = 0;
                for (int i = y; i <= n; i += x) {
                    ans += a[i];
                }
                cout << ans << endl;
            } else {
                cout << f[x][y] << endl;
            }
        } else {
            for (int j = 1; j < b; ++j) {
                f[j][x % j] = f[j][x % j] - a[x] + y;
            }
            a[x] = y;
        }
    }
    return 0;
}

