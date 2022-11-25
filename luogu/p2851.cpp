#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, T;
    cin >> n >> T;
    vector<int> v(n);
    int V2 = -1;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        V2 = max(V2, v[i] * v[i]);
    }
    const int INF = 1e4 + V2 * 4;
    int TT = T + 2 * V2;
    vector<int> f(TT + 1, INF);
    f[0] = 0;
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        int k = 1;
        while (k <= c) {
            for (int j = TT; j >= k * v[i]; --j) {
                f[j] = min(f[j], f[j - k * v[i]] + k);
            }
            c -= k;
            k *= 2;
        }
        if (c) {
            for (int j = TT; j >= c * v[i]; --j) {
                f[j] = min(f[j], f[j - c * v[i]] + c);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = TT - v[i]; j >= 0; --j) {
            f[j] = min(f[j], f[j + v[i]] + 1);
        }
    }
    if (f[T] == INF) cout << -1 << endl;
    else cout << f[T] << endl;
    return 0;
}

