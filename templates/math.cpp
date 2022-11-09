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

long long floor_div(long long a, long long b) {
    return a / b - ((a ^ b) < 0 && a % b != 0);
}

vector<int> calc(int n, int MOD) {
    vector<int> inv(n + 1, 0);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (long long)(MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    return inv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}

