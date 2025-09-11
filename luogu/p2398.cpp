#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> f(n + 1, 0);
    long long ans = 0;
    for (int i = n; i >= 1; --i) {
        f[i] = (long long)(n / i) * (n / i);
        for (int j = i + i; j <= n; j += i) f[i] -= f[j];
        ans += f[i] * i;
    }
    cout << ans << endl;
    return 0;
}

