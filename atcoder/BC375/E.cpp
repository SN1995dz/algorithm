#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        sum += b[i];
    }
    if (sum % 3 != 0) {
        cout << -1 << endl;
        return 0;
    }
    int target = sum / 3;
    const int INF = 1e9;
    vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(target + 1, vector<int>(target + 1, INF)));
    f[0][0][0] = 0;
    int curSum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= target; ++j) {
            for (int k = 0; k <= target; ++k) {
                if (f[i][j][k] == INF) continue;
                if (a[i] == 1) {
                    if (j + b[i] <= target) {
                        f[i + 1][j + b[i]][k] = min(f[i + 1][j + b[i]][k], f[i][j][k]);
                    }
                    if (k + b[i] <= target) {
                        f[i + 1][j][k + b[i]] = min(f[i + 1][j][k + b[i]], f[i][j][k] + 1);
                    }
                    if (curSum - j - k + b[i] <= target) {
                        f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k] + 1);
                    }
                } else if (a[i] == 2) {
                    if (j + b[i] <= target) {
                        f[i + 1][j + b[i]][k] = min(f[i + 1][j + b[i]][k], f[i][j][k] + 1);
                    }
                    if (k + b[i] <= target) {
                        f[i + 1][j][k + b[i]] = min(f[i + 1][j][k + b[i]], f[i][j][k]);
                    }
                    if (curSum - j - k + b[i] <= target) {
                        f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k] + 1);
                    }
                } else {
                    if (j + b[i] <= target) {
                        f[i + 1][j + b[i]][k] = min(f[i + 1][j + b[i]][k], f[i][j][k] + 1);
                    }
                    if (k + b[i] <= target) {
                        f[i + 1][j][k + b[i]] = min(f[i + 1][j][k + b[i]], f[i][j][k] + 1);
                    }
                    if (curSum - j - k + b[i] <= target) {
                        f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k]);
                    }
                }
            }
        }
        curSum += b[i];
    }
    if (f[n][target][target] == INF) cout << -1 << endl;
    else cout << f[n][target][target] << endl;
    return 0;
}

