#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> w(m), v(m);
    for (int i = 0; i < m; ++i) cin >> w[i] >> v[i];
    vector<int> f(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = n - w[i]; j >= 0; --j) {
            f[j + w[i]] = max(f[j + w[i]], f[j] + v[i]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = max(f[i], f[i - 1]);
    }
    cout << f[n] << endl;
    return 0;
}

