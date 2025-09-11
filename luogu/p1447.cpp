#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int g = min(n, m);
    vector<long long> f(g + 1, 0);
    for (int i = g; i >= 1; --i) {
        f[i] = (long long)(n / i) * (m / i);
        for (int j = i + i; j <= g; j += i) f[i] -= f[j];
    }
    long long ans = 0;
    for (int i = 1; i <= g; ++i) {
        ans += f[i] * (2 * (i - 1) + 1);
    }
    cout << ans << endl;
    return 0;
}

