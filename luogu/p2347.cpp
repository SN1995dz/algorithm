#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int> a(6);
    const int w[6] = {1, 2, 3, 5, 10, 20};
    for (int i = 0; i < 6; ++i) cin >> a[i];
    vector<vector<int>> f(7, vector<int>(1001, -1));
    f[0][0] = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j <= 1000; ++j) {
            if (f[i][j] >= 0) f[i + 1][j] = a[i];
        }
        for (int j = 0; j + w[i] <= 1000; ++j) {
            if (f[i + 1][j] > 0) {
                f[i + 1][j + w[i]] = max(f[i + 1][j + w[i]], f[i + 1][j] - 1);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= 1000; ++i) ans += (f[6][i] >= 0);
    cout << "Total=" << ans << endl;
    return 0;
}

