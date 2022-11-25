#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int s, n, m;
    cin >> s >> n >> m;
    vector<vector<int>> a(n, vector<int>(s));
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[j][i];
        }
    }
    for (int i = 0; i < n; ++i) {
        sort(a[i].begin(), a[i].end());
    }
    vector<int> f(m + 1, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = m; j >= 0; --j) {
            for (int k = 1; k <= s && j >= a[i][k - 1] * 2 + 1; ++k) {
                f[j] = max(f[j], f[j - (a[i][k - 1] * 2 + 1)] + k * (i + 1));
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}

