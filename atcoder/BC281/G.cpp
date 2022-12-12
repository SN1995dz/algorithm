#include <bits/stdc++.h>

using namespace std;

// @param m '1 <= m'
// @return x mod m
long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// @param n '0 <= n'
// @param m '1 <= m'
// @return '(x ** n) % m'
long long pow_mod(long long x, long long n, int m) {
    assert(0 <= n && 1 <= m);
    if (m == 1) return 0;
    long long r = 1, y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = r * y % m;
        y = y * y % m;
        n >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector C(n, vector<int>(n, 0));
    C[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % m;
        }
    }
    vector<int> pow2(n * n);
    pow2[0] = 1;
    for (int i = 1; i < n * n; ++i) pow2[i] = pow2[i - 1] * 2 % m;
    vector f(n, vector<int>(n, 0));
    f[1][1] = 1;
    for (int i = 1; i <= n - 2; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (f[i][j] == 0) continue;
            int tmp = (pow2[j] + m - 1) % m;
            int p = 1;
            for (int k = 1; k <= n - 1 - i; ++k) {
                p = (long long)p * tmp % m;
                f[i + k][k] = (f[i + k][k] + (long long)f[i][j] * p % m * C[n - 1 - i][k] % m * pow2[k * (k - 1) / 2] % m) % m;
                //f[i + k][k] = (f[i + k][k] + f[i][j] * pow_mod(pow2[j] + m - 1, k, m) % m * C[n - 1 - i][k] % m * pow2[k * (k - 1) / 2] % m) % m;
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= n - 2; ++j) {
        ans = (ans + (long long)f[n - 1][j] * (pow2[j] + m - 1) % m) % m;
    }
    cout << ans << endl;
    return 0;
}

