#include <bits/stdc++.h>

using namespace std;

vector<int> calc(int n, int MOD) {
    vector<int> inv(n + 1, 0);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (long long)(MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    return inv;
}

void solve() {
    const int MOD = 1e9 + 7;
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector f = vector(n, vector(n, vector<int>(n, -1)));
    vector<int> fac(n + 1);
    fac[0] = 1;
    vector<int> inv = calc(n, MOD);
    for (int i = 1; i <= n; ++i) {
        fac[i] = (long long)fac[i - 1] * i % MOD;
    }
    function<int(int, int, int)> dfs = [&](int l, int r, int k) {
        if (k < 0) return 0;
        if (k > r - l + 1) return 0;
        if (l >= r) return 1;
        if (f[l][r][k] != -1) return f[l][r][k];
        int res = 0;
        res = (res + dfs(l, r - 1, k)) % MOD;
        res = (res + dfs(l + 1, r, k)) % MOD;
        res = (res + MOD - dfs(l + 1, r - 1, k)) % MOD;
        if (s[l] == s[r]) {
            res = (res + dfs(l + 1, r - 1, k - 2)) % MOD;
        }
        return f[l][r][k] = res;
    };
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + (long long)dfs(0, n - 1, i) * fac[n - i] % MOD * fac[i] % MOD) % MOD;
    }
    for (int i = 1; i <= n; ++i) ans = (long long)ans * inv[i] % MOD;
    cout << ans << endl;
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

