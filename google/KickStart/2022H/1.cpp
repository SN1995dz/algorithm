#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> f(n + 1, n);
    f[1] = 1;
    for (int i = 1; i < n; ++i) {
        f[i + 1] = min(f[i + 1], f[i] + 1);
        for (int j = i + i, cnt = 1; j <= n; j += i, ++cnt) {
            f[j] = min(f[j], f[i] + 4 + cnt * 2);
        }
    }
    cout << f[n] << endl;
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

